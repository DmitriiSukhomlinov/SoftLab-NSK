#include "FaceFinder.h"

#include "..\Utils\Check.h"
#include <io.h>
#include <algorithm>
#include <direct.h>
#include <filesystem>
/*************************************/
/*************FaceFinder**************/
/*************************************/

const std::string FaceFinder::PICTURES_DIRECTORY = getPicturesDirectory();

std::string FaceFinder::getPicturesDirectory() {
    TCHAR currentDir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentDir);
    return std::string(currentDir) + "\\pictures\\";
}

const std::map<IFaceFinder::ColorDepth, FSDK_IMAGEMODE> FaceFinder::COLOR_DEPTH_CORRELATION  = { {ColorDepth::Bit8, FSDK_IMAGE_GRAYSCALE_8BIT},
                                                                                                 {ColorDepth::Bit24, FSDK_IMAGE_COLOR_24BIT}, 
                                                                                                 {ColorDepth::Bit32, FSDK_IMAGE_COLOR_32BIT} };
const double FaceFinder::SIMILARITY_THRESHOLD = 0.75;
const int FaceFinder::MAX_FACE_COUNT = 10;

FaceFinder::FaceFinder() {
}

FaceFinder::~FaceFinder() {
    clearAll();
}

void FaceFinder::init() {
    cout << "FaceFinder initializing";
    clearAll();
    std::filesystem::remove_all(std::filesystem::path(PICTURES_DIRECTORY));
}


void FaceFinder::addImage(const int _frameNumber, void* inputVideoBuffer, const int xPictureSize, const int yPictureSize, const int scanLine, const ColorDepth colorDepth) {
    HImage image;
    unsigned char* data = static_cast<unsigned char*>(inputVideoBuffer);
    FSDK_IMAGEMODE mode = COLOR_DEPTH_CORRELATION.at(colorDepth);
    int result = FSDK_LoadImageFromBuffer(&image, data, xPictureSize, yPictureSize, scanLine, mode);//!
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(result == FSDKE_OK, "Error in the loading process, error code " << result, );
    if (result != FSDKE_OK) {
        FSDK_FreeImage(image);
        cout << "Error in the loading process, error code " << result;
        return;
    }

    int facesCount = 0;
    shared_ptr<TFacePosition> facePositionPointer(new TFacePosition[MAX_FACE_COUNT]);
    //result = FSDK_SaveImageToFile(*image.get(), "F:/new.pick");
    //Есть вопрос выбора этого значения.
    //Если у нас изображение с глубиной цвета 24 бит и на нем есть два лица, то для того, чтобы они оба оказались определены, 
    //значение maxSizeInBytes нужно выставить на 24*2=48 как минимум. Если выставить от 24 до 48, то найдется только одно лицо. 
    //Если меньше 24 - то не найдет ни одного
    //Кстати, это можно обработать, потому что если он не вернет лиц из-за недостаточного значения, то код ошибки будет FSDKE_INSUFFICIENT_BUFFER_SIZE(-8)
    result = FSDK_DetectMultipleFaces(image, &facesCount, facePositionPointer.get(), sizeof(TFacePosition) * MAX_FACE_COUNT);
    if (result == FSDKE_FACE_NOT_FOUND) {
        saveNotFound(_frameNumber, image);
    }
    if (facesCount == 0) {
        FSDK_FreeImage(image);
        return;
    }
    
    TFacePosition* facePositionArray = facePositionPointer.get();
    for (int i = 0; i < facesCount; i++) {
        std::shared_ptr<FSDK_FaceTemplate> faceTemplate(new FSDK_FaceTemplate);
        auto fpa = &facePositionArray[i];
        result = FSDK_GetFaceTemplateInRegion(image, fpa, faceTemplate.get());
        CHECK_IF_FALSE_CONTINUE(result == FSDKE_OK, "Cannot get face template, error code " << result);

        bool createNewFaceDesription = true;
        for (auto& tmpDesc : tempDescriptions) {
            float similarity = 0.0;
            result = FSDK_MatchFaces(faceTemplate.get(), tmpDesc->faceTemplate, &similarity);
            CHECK_IF_FALSE_CONTINUE_NO_MESSAGE((similarity >= SIMILARITY_THRESHOLD));

            createNewFaceDesription = false;
            bool addToExistRegion = false;
            for (FrameRegion* frame : tmpDesc->frameRegions) {
                CHECK_IF_FALSE_CONTINUE_NO_MESSAGE((frame->start + frame->duration == _frameNumber));
                frame->duration++;
                addToExistRegion = true;
                break;
            }

            if (!addToExistRegion) {
                FrameRegion* newFrame = new FrameRegion(_frameNumber);//ПРОВЕРИТЬ!!!
                tmpDesc->frameRegions.push_back(newFrame);
            }
            // выбрать лучшее лицо
            if (isNewFaceBetter(tmpDesc->faceTemplate, faceTemplate.get())) {
                tmpDesc->bestFrame = _frameNumber;
                //delete tmpDesc->facePosition;
                tmpDesc->facePosition = new TFacePosition (facePositionArray[i]);//ПРОВЕРИТЬ!!!!
                //delete tmpDesc->faceTemplate;
                CopyMemory(tmpDesc->faceTemplate, faceTemplate.get(), sizeof(FSDK_FaceTemplate));
            }

            saveAlreadyFound(_frameNumber, image, tmpDesc);
        }

        if (createNewFaceDesription) {
            tempDescriptions.push_back(new FaceDescriptionTemp(_frameNumber, new TFacePosition(facePositionArray[i]), new FSDK_FaceTemplate(*faceTemplate.get())));

            saveFirstTime(_frameNumber, image);
        }

        /*
        //Проверим если уже есть в массиве
        for (auto& v : descriptions) {
            //Вот тут у меня возникает закономерный вопрос - какием образом мне здесь провернуть операцию присваивания, чтобы в FSDK_FaceTemplate поместить то, что у нас сохранено?
            FSDK_FaceTemplate* temp = reinterpret_cast<FSDK_FaceTemplate*>(v->faceDescrition->faceTemplate);
            float similarity = 0.0;
            result = FSDK_MatchFaces(faceTemplate, temp, &similarity);
            CHECK_IF_FALSE_CONTINUE_NO_MESSAGE((similarity >= SIMILARITY_THRESHOLD));

            for (FrameRegion* frame : v->frameRegions) {
                CHECK_IF_FALSE_CONTINUE_NO_MESSAGE((frame->start + frame->duration == _frameNumber));
                frame->duration++;
            }

            FrameRegion* newFrame = new FrameRegion(_frameNumber);
            v->frameRegions.push_back(newFrame);

            // выбрать лучшее лицо
            if (isNewFaceBetter()) {
                fillFaceDescription(v->faceDescrition, _frameNumber, facePositionArray[i].xc, facePositionArray[i].yc, facePositionArray[i].w, 0, (int)sizeof(*faceTemplate));
                CopyMemory(v->faceDescrition->faceTemplate, faceTemplate, sizeof(FSDK_FaceTemplate));
            }
            return;
        }
        FaceDescription* faceDescription = createFaceDescription((int)sizeof(FSDK_FaceTemplate));
        fillFaceDescription(faceDescription, _frameNumber, facePositionArray[i].xc, facePositionArray[i].yc, facePositionArray[i].w, 0, (int)sizeof(*faceTemplate));
        CopyMemory(faceDescription->faceTemplate, faceTemplate, sizeof(FSDK_FaceTemplate));
        FrameRegion* frame = new FrameRegion(_frameNumber);
        DescriptionData* descriptionData = new DescriptionData(faceDescription, std::vector<FrameRegion*>() = { frame });

        descriptions.push_back(descriptionData);*/
    }
    FSDK_FreeImage(image);
}

void FaceFinder::finish() {
    cout << "FaceFinder finalizing";

    //std::vector<FaceDescriptionTemp*> roughtTempDescriptions;
    //for (auto tmpDesc : tempDescriptions) {
    //    for (auto tmpDesc2 : tempDescriptions) {
    //        CHECK_IF_FALSE_CONTINUE_NO_MESSAGE(tmpDesc)
    //    }
    //}


    for (const auto& tmpDesc : tempDescriptions) {
        FaceDescription* faceDescription = createFaceDescription((int)sizeof(FSDK_FaceTemplate));
        fillFaceDescription(faceDescription, tmpDesc->bestFrame, tmpDesc->facePosition->xc, tmpDesc->facePosition->yc, tmpDesc->facePosition->w, 0, (int)sizeof(*tmpDesc->faceTemplate));
        CopyMemory(faceDescription->faceTemplate, tmpDesc->faceTemplate, sizeof(FSDK_FaceTemplate));
        std::vector<FrameRegion*> descriptionFrameRegions;
        for (auto& region : tmpDesc->frameRegions) {
            descriptionFrameRegions.push_back(new FrameRegion(*region));
        }
        DescriptionData* descriptionData = new DescriptionData(faceDescription, descriptionFrameRegions);

        descriptions.push_back(descriptionData);
    }
    clearTempDescriptions();
    //Что завершать тоже не очень понятно
    //Хотя, насчет завершения, я полагаю, что в этот момент мы будем писать то, что было наработано в базу
    //Правда, я пока что не до конца представляю, как именно это будет делаться
    //Хотя, если правильно помню, нужно переорганизовать массив

    //сравнение с другим порогом (грубее)

    //скопировать из frameNumber, TFacePosition, FSDK_FaceTemplate в DescriptionData*
}

int FaceFinder::faceCount() const {
    return int(descriptions.size());
}

FaceDescription* FaceFinder::getFaceInfo(int index) const {
    CHECK_IF_FALSE((index < descriptions.size()), nullptr);

    std::cout << "Index № " << index << " for the \"getFaceInfo\" function was found.";
    return descriptions.at(index)->faceDescrition;
}

int FaceFinder::frameRegionsNum(int index) const {
    CHECK_IF_FALSE((index < descriptions.size()), -1);

    std::cout << "Index № " << index << " for the \"frameRegionsNum\" function was found.";
    return int(descriptions.at(index)->frameRegions.size());
}

FrameRegion* FaceFinder::getFaceRegionByIndex(int index, int frameNum) const {
    CHECK_IF_FALSE((index < descriptions.size()), nullptr);
    CHECK_IF_FALSE((0 <= frameNum) && (frameNum < descriptions.at(frameNum)->frameRegions.size()), nullptr);

    std::cout << "Index № " << index << " for the \"getFaceRegionByIndex\" function was found.";
    return descriptions.at(frameNum)->frameRegions.at(frameNum);
}

bool FaceFinder::isNewFaceBetter(FSDK_FaceTemplate* currentFace, FSDK_FaceTemplate* newFace) const {
    float currentTemplateNorm = (float)currentFace->ftemplate[12];
    float newTemplateNorm = (float)newFace->ftemplate[12];
    return currentTemplateNorm < newTemplateNorm;
}

void FaceFinder::clearDescriptions() {
    for (auto& desc : descriptions) {
        delete desc;
    }
    descriptions.clear();
}

void FaceFinder::clearTempDescriptions() {
    for (auto& tmpDesc : tempDescriptions) {
        delete tmpDesc;
    }
    tempDescriptions.clear();
}

void FaceFinder::clearAll() {
    clearDescriptions();
    clearTempDescriptions();
}

void FaceFinder::saveNotFound(const int frameNumber, HImage image) {
    cout << "Frame " << frameNumber << ": face is not found." << endl;
    const std::string not_found = PICTURES_DIRECTORY + "not_found\\";
    std::filesystem::create_directories(std::filesystem::path(not_found));
    std::string out = not_found + to_string(frameNumber) + ".bmp";
    FSDK_SaveImageToFile(image, out.c_str());
}

void FaceFinder::saveFirstTime(const int frameNumber, HImage image) {
    cout << "Frame " << frameNumber << ": new group is created." << endl;
    const std::string newDir = PICTURES_DIRECTORY + to_string(tempDescriptions.size()) + "\\";
    std::filesystem::create_directories(std::filesystem::path(newDir));
    std::string out = newDir + to_string(frameNumber) + ".bmp";
    FSDK_SaveImageToFile(image, out.c_str());
}

void FaceFinder::saveAlreadyFound(const int frameNumber, HImage image, FaceDescriptionTemp* tmpDesc) {
    int num = -1;
    for (int j = 0; j < tempDescriptions.size(); j++) {
        if (tmpDesc == tempDescriptions[j]) {
            num = j + 1;
            break;
        }
    }
    cout << "Frame " << frameNumber << ": added to the existing group # " << num << endl;
    const std::string dir = PICTURES_DIRECTORY + to_string(num) + "\\";
    std::string out = dir + to_string(frameNumber) + ".bmp";
    int result = FSDK_SaveImageToFile(image, out.c_str());
    int qwe = 0;
}


/*************************************/
/************DescriptionData**********/
/*************************************/

FaceFinder::DescriptionData::DescriptionData(FaceDescription* _faceDescrition, const std::vector<FrameRegion*>& _frameRegions) 
    : faceDescrition(_faceDescrition), frameRegions(_frameRegions) {}

FaceFinder::DescriptionData::~DescriptionData() {
    delete faceDescrition;
    for (auto& region : frameRegions) {
        delete region;
    }
}

/*************************************/
/**********FaceDescriptionTemp*******/
/*************************************/

FaceFinder::FaceDescriptionTemp::FaceDescriptionTemp() : bestFrame(-1), facePosition(nullptr), faceTemplate(nullptr) {}

FaceFinder::FaceDescriptionTemp::FaceDescriptionTemp(const int _bestFrame, TFacePosition* _facePosition, FSDK_FaceTemplate* _faceTemplate) :
    bestFrame(_bestFrame), facePosition(_facePosition), faceTemplate(_faceTemplate) {
    frameRegions.push_back(new FrameRegion(_bestFrame));
}

FaceFinder::FaceDescriptionTemp::~FaceDescriptionTemp() {
    for (auto& region : frameRegions) {
        delete region;
    }
    delete facePosition;
    delete faceTemplate;
}

void FaceFinder::FaceDescriptionTemp::clear() {
    bestFrame = -1;
    frameRegions.clear();
    facePosition = nullptr;
    faceTemplate = nullptr;
}
