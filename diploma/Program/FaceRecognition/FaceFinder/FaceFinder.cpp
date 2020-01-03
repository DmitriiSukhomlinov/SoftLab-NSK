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
        delete desc.second;
    }
}

void FaceFinder::init() {
    //Не совсем понимаю, что тут нужно инициализировать
}

void FaceFinder::addImage(const int frameNumber, void* inputVideoBuffer, const int xPictureSize, const int yPictureSize, const int scanLine, const ColorDepth colorDepth) {
    shared_ptr<HImage> image(new HImage);
    bool result = FSDK_LoadImageFromBuffer(image.get(), static_cast<unsigned char*>(inputVideoBuffer), xPictureSize, yPictureSize, scanLine, COLOR_DEPTH_CORRELATION.at(colorDepth));//!
    CHECK_RETURN_NO_OK_MESSAGE(result == FSDKE_OK, "Error in the loading process, error code " << result, );

    int facesCount = 0;
    shared_ptr<TFacePosition> facePositionPointer(new TFacePosition);
    //Есть вопрос выбора этого значения.
    //Если у нас изображение с глубиной цвета 24 бит и на нем есть два лица, то для того, чтобы они оба оказались определены, 
    //значение maxSizeInBytes нужно выставить на 24*2=48 как минимум. Если выставить от 24 до 48, то найдется только одно лицо. 
    //Если меньше 24 - то не найдет ни одного
    //Кстати, это можно обработать, потому что если он не вернет лиц из-за недостаточного значения, то код ошибки будет FSDKE_INSUFFICIENT_BUFFER_SIZE(-8)
    const int maxSizeInBytes = 1024;
    result = FSDK_DetectMultipleFaces(*image.get(), &facesCount, facePositionPointer.get(), maxSizeInBytes);
    CHECK_RETURN_NO_OK_MESSAGE(result == FSDKE_OK, "Error in the face detecting process, error code " << result, );
    CHECK(facesCount != 0, );

    TFacePosition* facePositionArray = facePositionPointer.get();
    for (int i = 0; i < facesCount; i++) {
        FSDK_FaceTemplate* faceTemplate = new FSDK_FaceTemplate;
        result = FSDK_GetFaceTemplateInRegion(*image, &facePositionArray[i], faceTemplate);
        CHECK_CONTINUE(result == FSDKE_OK, "Cannot get face template, error code " << result);

        //Проверим если уже есть в массиве
        for (auto& v : descriptions) {
            //Вот тут у меня возникает закономерный вопрос - какием образом мне здесь провернуть операцию присваивания, чтобы в FSDK_FaceTemplate поместить то, что у нас сохранено?
            FSDK_FaceTemplate* temp = reinterpret_cast<FSDK_FaceTemplate*>(v.second->faceDescrition->faceTemplate);
            float similarity = 0.0;
            result = FSDK_MatchFaces(faceTemplate, temp, &similarity);
            CHECK_CONTINUE_NO_MESSAGE((similarity >= SIMILARITY_THRESHOLD));
            
            bool newRegion = true;
            for (FrameRegion* frame : v.second->frameRegions) {
                CHECK_CONTINUE_NO_MESSAGE((frame->start + frame->duration == frameNumber));

                frame->duration++;
                newRegion = false;
                break;
            }

            if (newRegion) {
                FrameRegion* newFrame = new FrameRegion(frameNumber);
                //Проблема как и ниже - не совсем понимаю, как работает функция insert в стандартной библиотеке вектора. Подскажите, пожалуйста)
                //v.second.frameRegions.insert(newFrame);
                return;
            }
        }


        FaceDescription::FaceDescriptionHeader header(0, facePositionArray[i].xc, facePositionArray[i].yc, facePositionArray[i].w, 0, (int)sizeof(*faceTemplate));
        FaceDescription* faceDescription = new FaceDescription(header, faceTemplate->ftemplate[0]);
        FrameRegion* frame = new FrameRegion(frameNumber, 1);
        DescriptionData* descriptionData = new DescriptionData(faceDescription, std::vector<FrameRegion*>() = { frame });

        //Здесь мы вставляем ключ и значение
        //У меня немного не получилось разобраться, как работает мапа в c++ и как в нее вставить элемент
        //Дело в том, что я очень долго работал с Qt и там все немного по-другому.
        //Надеюсь, что вы мне подскажете или посоветуете, как по-дрегому организовать данные.
        //descriptions.insert(0, descriptionData);
    }
}

void FaceFinder::finish() {
    //Что завершать тоже не очень понятно
    //Хотя, насчет завершения, я полагаю, что в этот момент мы будем писать то, что было наработано в базу
    //Правда, я пока что не до конца представляю, как именно это будет делаться
    //Хотя, если правильно помню, нужно переорганизовать массив
}

int FaceFinder::faceCount() const {
    return int(descriptions.size());
}

FaceDescription* FaceFinder::getFaceInfo(int index) const {
    CHECK((index < descriptions.size()), nullptr);

    std::cout << "Index № " << index << " for the \"getFaceInfo\" function was found.";
    return descriptions.at(index)->faceDescrition;
}

int FaceFinder::frameRegionsNum(int index) const {
    CHECK((index < descriptions.size()), -1);

    std::cout << "Index № " << index << " for the \"frameRegionsNum\" function was found.";
    return int(descriptions.at(index)->frameRegions.size());
}

FrameRegion* FaceFinder::getFaceRegionByIndex(int index, int frameNum) const {
    CHECK((index < descriptions.size()), nullptr);
    CHECK((0 <= frameNum) && (frameNum < descriptions.at(frameNum)->frameRegions.size()), nullptr);

    std::cout << "Index № " << index << " for the \"getFaceRegionByIndex\" function was found.";
    return descriptions.at(frameNum)->frameRegions.at(frameNum);
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
