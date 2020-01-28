#include "FaceFinder.h"

#include "..\Utils\Check.h"

/*************************************/
/*************FaceFinder**************/
/*************************************/

const std::map<IFaceFinder::ColorDepth, FSDK_IMAGEMODE> FaceFinder::COLOR_DEPTH_CORRELATION  = { {ColorDepth::Bit8, FSDK_IMAGE_GRAYSCALE_8BIT},
                                                                                                 {ColorDepth::Bit24, FSDK_IMAGE_COLOR_24BIT}, 
                                                                                                 {ColorDepth::Bit32, FSDK_IMAGE_COLOR_32BIT} };
const double FaceFinder::SIMILARITY_THRESHOLD = 0.75;

FaceFinder::FaceFinder() {
}

FaceFinder::~FaceFinder() {
    for (auto& desc : descriptions) {
        delete desc;
    }
}

void FaceFinder::init() {
    descriptions.clear();
    tempDescriptions.clear();
}

//void FaceFinder::addImage(const int _frameNumber, void* inputVideoBuffer, const int xPictureSize, const int yPictureSize, const int scanLine, const ColorDepth colorDepth) {
void FaceFinder::addImage(const int _frameNumber, const std::string& path) {
    shared_ptr<HImage> image(new HImage);
    //bool result = FSDK_LoadImageFromBuffer(image.get(), static_cast<unsigned char*>(inputVideoBuffer), xPictureSize, yPictureSize, scanLine, COLOR_DEPTH_CORRELATION.at(colorDepth));//!
    int result = FSDK_LoadImageFromFile(image.get(), path.c_str());//!
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(result == FSDKE_OK, "Error in the loading process, error code " << result, );

    int facesCount = 0;
    shared_ptr<TFacePosition> facePositionPointer(new TFacePosition);
    //Есть вопрос выбора этого значения.
    //Если у нас изображение с глубиной цвета 24 бит и на нем есть два лица, то для того, чтобы они оба оказались определены, 
    //значение maxSizeInBytes нужно выставить на 24*2=48 как минимум. Если выставить от 24 до 48, то найдется только одно лицо. 
    //Если меньше 24 - то не найдет ни одного
    //Кстати, это можно обработать, потому что если он не вернет лиц из-за недостаточного значения, то код ошибки будет FSDKE_INSUFFICIENT_BUFFER_SIZE(-8)
    const int maxSizeInBytes = 1024;
    result = FSDK_DetectMultipleFaces(*image.get(), &facesCount, facePositionPointer.get(), maxSizeInBytes);
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(result == FSDKE_OK, "Error in the face detecting process, error code " << result, );
    CHECK_IF_FALSE(facesCount != 0, );

    TFacePosition* facePositionArray = facePositionPointer.get();
    for (int i = 0; i < facesCount; i++) {
        FSDK_FaceTemplate* faceTemplate = new FSDK_FaceTemplate;
        result = FSDK_GetFaceTemplateInRegion(*image, &facePositionArray[i], faceTemplate);
        CHECK_IF_FALSE_CONTINUE(result == FSDKE_OK, "Cannot get face template, error code " << result);

        bool createNewFaceDesription = true;
        for (auto& tmpDesc : tempDescriptions) {
            float similarity = 0.0;
            result = FSDK_MatchFaces(faceTemplate, tmpDesc->faceTemplate, &similarity);
            CHECK_IF_FALSE_CONTINUE_NO_MESSAGE((similarity >= SIMILARITY_THRESHOLD));

            createNewFaceDesription = false;
            bool addToExistRegion = false;
            for (FrameRegion* frame : tmpDesc->frameRegions) {
                CHECK_IF_FALSE_CONTINUE_NO_MESSAGE((frame->start + frame->duration == _frameNumber));
                frame->duration++;
                addToExistRegion = true;
            }

            if (!addToExistRegion) {
                FrameRegion* newFrame = new FrameRegion(_frameNumber);//ПРОВЕРИТЬ!!!
                tmpDesc->frameRegions.push_back(newFrame);
            }

            // выбрать лучшее лицо
            if (isNewFaceBetter()) {
                tmpDesc->bestFrame = _frameNumber;
                tmpDesc->facePosition = &facePositionArray[i];//ПРОВЕРИТЬ!!!!
                tmpDesc->faceTemplate = faceTemplate;
            }
        }

        if (createNewFaceDesription) {
            tempDescriptions.push_back(new FaceDescriptionTemp(_frameNumber, &facePositionArray[i], faceTemplate));
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
}

void FaceFinder::finish() {
    for (auto& tmpDesc : tempDescriptions) {
        FaceDescription* faceDescription = createFaceDescription((int)sizeof(FSDK_FaceTemplate));
        fillFaceDescription(faceDescription, tmpDesc->bestFrame, tmpDesc->facePosition->xc, tmpDesc->facePosition->yc, tmpDesc->facePosition->w, 0, (int)sizeof(*tmpDesc->faceTemplate));
        CopyMemory(faceDescription->faceTemplate, tmpDesc->faceTemplate, sizeof(FSDK_FaceTemplate));
        DescriptionData* descriptionData = new DescriptionData(faceDescription, tmpDesc->frameRegions);

        descriptions.push_back(descriptionData);
    }
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

bool FaceFinder::isNewFaceBetter() const {

    return true;
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

}

void FaceFinder::FaceDescriptionTemp::clear() {
    bestFrame = -1;
    frameRegions.clear();
    facePosition = nullptr;
    faceTemplate = nullptr;
}
