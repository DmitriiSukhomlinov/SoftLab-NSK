#include "FaceFinder.h"

#include "..\Utils\Check.h"
#include <io.h>
#include <algorithm>
#include <direct.h>
#include <filesystem>


#include <iostream>     // std::cout, std::ostream, std::ios
#include <fstream>  
/*************************************/
/*************FaceFinder**************/
/*************************************/

const std::string FaceFinder::PICTURES_HIGHT_DIRECTORY = getPicturesHightDirectory();

const std::string FaceFinder::PICTURES_LOW_DIRECTORY = getPicturesLowDirectory();


std::string FaceFinder::getPicturesHightDirectory() {
    TCHAR currentDir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentDir);
    return std::string(currentDir) + "\\pictures\\hight\\";
}


std::string FaceFinder::getPicturesLowDirectory() {
    TCHAR currentDir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentDir);
    return std::string(currentDir) + "\\pictures\\low\\";
}


const std::map<IFaceFinder::ColorDepth, FSDK_IMAGEMODE> FaceFinder::COLOR_DEPTH_CORRELATION  = { {ColorDepth::Bit8, FSDK_IMAGE_GRAYSCALE_8BIT},
                                                                                                 {ColorDepth::Bit24, FSDK_IMAGE_COLOR_24BIT}, 
                                                                                                 {ColorDepth::Bit32, FSDK_IMAGE_COLOR_32BIT} };
const int FaceFinder::MAX_FACE_COUNT = 10;

FaceFinder::FaceFinder() : 
    hightSimilarityThreshold(0.0), 
    lowSimilarityThreshold(0.0),
    time(0) {}

FaceFinder::~FaceFinder() {
    clearAll();
}

void FaceFinder::init(const double firstThreshold, const double secondThreshold) {
    tc.startTimer();
    hightSimilarityThreshold = firstThreshold;
    lowSimilarityThreshold = secondThreshold;
    cout << "FaceFinder initializing";
    clearAll();
    time += tc.checkTimer();
    std::filesystem::remove_all(std::filesystem::path(PICTURES_HIGHT_DIRECTORY));
    std::filesystem::remove_all(std::filesystem::path(PICTURES_LOW_DIRECTORY));
}


void FaceFinder::addImage(const int _frameNumber, void* inputVideoBuffer, const int xPictureSize, const int yPictureSize, const int scanLine, const ColorDepth colorDepth) {
    tc.startTimer();
    HImage image;
    unsigned char* data = static_cast<unsigned char*>(inputVideoBuffer);
    FSDK_IMAGEMODE mode = COLOR_DEPTH_CORRELATION.at(colorDepth);
    int result = FSDK_LoadImageFromBuffer(&image, data, xPictureSize, yPictureSize, scanLine, mode);//!
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(result == FSDKE_OK, "Error in the loading process, error code " << result, );
    if (result != FSDKE_OK) {
        FSDK_FreeImage(image);
        cout << "Error in the loading process, error code " << result;
        time += tc.checkTimer();
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
        time += tc.checkTimer();
        return;
    }
    
    TFacePosition* facePositionArray = facePositionPointer.get();
    for (int i = 0; i < facesCount; i++) {
        std::shared_ptr<FSDK_FaceTemplate> faceTemplate(new FSDK_FaceTemplate);
        result = FSDK_GetFaceTemplateInRegion(image, &facePositionArray[i], faceTemplate.get());
        CHECK_IF_FALSE_CONTINUE(result == FSDKE_OK, "Cannot get face template, error code " << result);

        bool createNewFaceDesription = true;
        for (auto& tmpDesc : tempDescriptions) {
            float similarity = 0.0;
            result = FSDK_MatchFaces(faceTemplate.get(), tmpDesc->faceTemplate, &similarity);
            CHECK_IF_FALSE_CONTINUE_NO_MESSAGE((similarity >= hightSimilarityThreshold));

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
    }
    FSDK_FreeImage(image);
    time += tc.checkTimer();
}

void FaceFinder::finish() {
    tc.startTimer();
    cout << "FaceFinder finalizing";

    int prevSize = (int)tempDescriptions.size();
    std::vector<FaceDescriptionTemp*> toRemove;
    auto notToRemove = [&toRemove](FaceDescriptionTemp* reg) -> bool {
        return std::find(toRemove.begin(), toRemove.end(), reg) == toRemove.end();
    };

    for (auto tmpDesc : tempDescriptions) {
        CHECK_IF_FALSE_CONTINUE_NO_MESSAGE(notToRemove(tmpDesc));
        for (auto tmpDesc2 : tempDescriptions) {
            CHECK_IF_FALSE_CONTINUE_NO_MESSAGE((*tmpDesc != *tmpDesc2));
            CHECK_IF_FALSE_CONTINUE_NO_MESSAGE(notToRemove(tmpDesc2));

            float similarity = 0.0;
            /*int result = */FSDK_MatchFaces(tmpDesc->faceTemplate, tmpDesc2->faceTemplate, &similarity);
            CHECK_IF_FALSE_CONTINUE_NO_MESSAGE((similarity >= lowSimilarityThreshold));

            if (isNewFaceBetter(tmpDesc->faceTemplate, tmpDesc2->faceTemplate)) {
                tmpDesc->bestFrame = tmpDesc2->bestFrame;
                tmpDesc->facePosition = new TFacePosition(*tmpDesc2->facePosition);
                CopyMemory(tmpDesc->faceTemplate, tmpDesc2->faceTemplate, sizeof(FSDK_FaceTemplate));
            }
            uniteRegions(tmpDesc->frameRegions, tmpDesc2->frameRegions);
            toRemove.push_back(tmpDesc2);
        }
        int i = 0;
    }

    for (auto remEl : toRemove) {
        tempDescriptions.erase(std::remove(tempDescriptions.begin(), tempDescriptions.end(), remEl), tempDescriptions.end());
        delete remEl;
    }
    
    std::filesystem::create_directories(std::filesystem::path(PICTURES_LOW_DIRECTORY));
    //std::filesystem::copy(filesystem::path(PICTURES_HIGHT_DIRECTORY + "not_found\\"), filesystem::path(PICTURES_LOW_DIRECTORY + "not_found\\"), filesystem::copy_options::recursive);
    for (int index = 0; index < tempDescriptions.size(); index++) {
        std::filesystem::create_directories(std::filesystem::path(PICTURES_LOW_DIRECTORY + to_string(index + 1) + "\\"));
        for (auto reg : tempDescriptions[index]->frameRegions) {
            for (int i = reg->start; i < reg->start + reg->duration; i++) {
                for (int j = 1; j <= prevSize; j++) {
                    string str = PICTURES_HIGHT_DIRECTORY + to_string(j) + "\\" + to_string(i) + ".bmp";
                    if (filesystem::exists(filesystem::path(str))) {
                        string newStr = PICTURES_LOW_DIRECTORY + to_string(index + 1) + "\\" + to_string(i) + ".bmp";
                        if (!filesystem::exists(newStr)) {
                            filesystem::copy_file(str, newStr);
                        }
                        break;
                    }
                }
            }
        }
    }


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
    time += tc.checkTimer();
    std::filebuf fb;
    fb.open("time.txt", std::ios::out);
    std::ostream fout(&fb);
    fout << time << " Microseconds";
    fb.close();
}

int FaceFinder::faceCount() const {
    return int(descriptions.size());
}

FaceDescription* FaceFinder::getFaceInfo(int index) const {
    CHECK_IF_FALSE((index < descriptions.size()), nullptr);

    //std::cout << "Index № " << index << " for the \"getFaceInfo\" function was found.";
    return descriptions.at(index)->faceDescrition;
}

int FaceFinder::frameRegionsNum(int index) const {
    CHECK_IF_FALSE((index < descriptions.size()), -1);

    //std::cout << "Index № " << index << " for the \"frameRegionsNum\" function was found.";
    return int(descriptions.at(index)->frameRegions.size());
}

FrameRegion* FaceFinder::getFaceRegionByIndex(int index, int frameNum) const {
    CHECK_IF_FALSE((index < descriptions.size()), nullptr);
    CHECK_IF_FALSE((0 <= frameNum) && (frameNum < descriptions.at(frameNum)->frameRegions.size()), nullptr);

    //std::cout << "Index № " << index << " for the \"getFaceRegionByIndex\" function was found.";
    return descriptions.at(index)->frameRegions.at(frameNum);
}

bool FaceFinder::isNewFaceBetter(FSDK_FaceTemplate* currentFace, FSDK_FaceTemplate* newFace) const {
    float currentTemplateNorm = (float)currentFace->ftemplate[12];
    float newTemplateNorm = (float)newFace->ftemplate[12];
    return currentTemplateNorm < newTemplateNorm;
}

void FaceFinder::uniteRegions(std::vector<FrameRegion*>& current, std::vector<FrameRegion*> additional) {
    std::vector<FrameRegion*> toRemove;
    auto notToRemove = [&toRemove](FrameRegion* reg) -> bool {
        return std::find(toRemove.begin(), toRemove.end(), reg) == toRemove.end();
    };
    for (auto currentReg : current) {
        for (auto addReg : additional) {
            CHECK_IF_FALSE_CONTINUE_NO_MESSAGE(notToRemove(addReg));
            //CHECK_IF_FALSE_CONTINUE_NO_MESSAGE((std::find(toRemove.begin(), toRemove.end(), addReg) == toRemove.end()));

            if (currentReg->intersect(addReg)) {
                toRemove.push_back(addReg);
                //additional.erase(std::remove(additional.begin(), additional.end(), addReg), additional.end());
            }
        }
    }
    for (auto remEl : toRemove) {
        additional.erase(std::remove(additional.begin(), additional.end(), remEl), additional.end());
    }
    toRemove.clear();

    for (auto currentReg : current) {
        CHECK_IF_FALSE_CONTINUE_NO_MESSAGE(notToRemove(currentReg));
        //CHECK_IF_FALSE_CONTINUE_NO_MESSAGE((std::find(toRemove.begin(), toRemove.end(), currentReg) == toRemove.end()));
        for (auto currentReg2 : current) {
            CHECK_IF_FALSE_CONTINUE_NO_MESSAGE((*currentReg != *currentReg2));
            CHECK_IF_FALSE_CONTINUE_NO_MESSAGE(notToRemove(currentReg2));
            //CHECK_IF_FALSE_CONTINUE_NO_MESSAGE((std::find(toRemove.begin(), toRemove.end(), currentReg2) == toRemove.end()));

            if (currentReg->intersect(currentReg2)) {
                toRemove.push_back(currentReg2);
                //current.erase(std::remove(current.begin(), current.end(), currentReg2), current.end());
            }
        }
    }

    for (auto remEl : toRemove) {
        current.erase(std::remove(current.begin(), current.end(), remEl), current.end());
        delete remEl;
    }

    for (FrameRegion* leftReg : additional) {
        current.push_back(new FrameRegion(*leftReg));
    }
    std::sort(std::begin(current), std::end(current), [](FrameRegion* a, FrameRegion* b) -> bool
    {
        return a->start < b->start;
    });
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
    const std::string not_found = PICTURES_HIGHT_DIRECTORY + "not_found\\";
    std::filesystem::create_directories(std::filesystem::path(not_found));
    std::string out = not_found + to_string(frameNumber) + ".bmp";
    //FSDK_SaveImageToFile(image, out.c_str());
}

void FaceFinder::saveFirstTime(const int frameNumber, HImage image) {
    cout << "Frame " << frameNumber << ": new group is created." << endl;
    const std::string newDir = PICTURES_HIGHT_DIRECTORY + to_string(tempDescriptions.size()) + "\\";
    std::filesystem::create_directories(std::filesystem::path(newDir));
    std::string out = newDir + to_string(frameNumber) + ".bmp";
    //FSDK_SaveImageToFile(image, out.c_str());
}

void FaceFinder::saveAlreadyFound(const int frameNumber, HImage image, FaceDescriptionTemp* tmpDesc) {
    int num = -1;
    for (int j = 0; j < tempDescriptions.size(); j++) {
        if (*tmpDesc == *tempDescriptions[j]) {//
            num = j + 1;
            break;
        }
    }
    cout << "Frame " << frameNumber << ": added to the existing group # " << num << endl;
    const std::string dir = PICTURES_HIGHT_DIRECTORY + to_string(num) + "\\";
    std::string out = dir + to_string(frameNumber) + ".bmp";
    //FSDK_SaveImageToFile(image, out.c_str());
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

bool FaceFinder::FaceDescriptionTemp::operator==(const FaceDescriptionTemp& other) const {
    bool frameEquals = this->bestFrame == other.bestFrame;
    CHECK_IF_FALSE(frameEquals, false);

    bool regionRegions = this->frameRegions.size() == other.frameRegions.size();
    CHECK_IF_FALSE(regionRegions, false);

    for (int i = 0; i < frameRegions.size(); i++) {
        regionRegions = regionRegions && this->frameRegions[i] == other.frameRegions[i];
    }
    CHECK_IF_FALSE(regionRegions, false);

    bool facePosition = this->facePosition->xc == other.facePosition->xc &&
                        this->facePosition->yc == other.facePosition->yc &&
                        this->facePosition->w == other.facePosition->w &&
                        this->facePosition->angle == other.facePosition->angle &&
                        this->facePosition->padding == other.facePosition->padding;
    CHECK_IF_FALSE(facePosition, false);

    int diff = std::strcmp(this->faceTemplate->ftemplate, other.faceTemplate->ftemplate);
    CHECK_IF_FALSE(diff == 0, false);

    return true;
}

bool FaceFinder::FaceDescriptionTemp::operator!=(const FaceDescriptionTemp& other) const {
    return !(*this == other);
}

void FaceFinder::FaceDescriptionTemp::clear() {
    bestFrame = -1;
    frameRegions.clear();
    facePosition = nullptr;
    faceTemplate = nullptr;
}
