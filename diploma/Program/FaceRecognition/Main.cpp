

#include "FaceSDK/LuxandFaceSDK.h"
#include "FaceFinder/IFaceFinder.h"
#include "FaceFinder/FaceFinder.h"
#include "Utils/Check.h"
#include "Utils/Consts.h"

#include <iostream>



unsigned char* readBmp(const std::string& path, BITMAPINFOHEADER& bmpInfo) {
    FILE* bmp = fopen(path.c_str(), "rb");//Открываем файл для чтения побитово, НАДО УБРАТЬ ВОРНИНГ!!!

    BITMAPFILEHEADER bmpHeader;
    fread(&bmpHeader, 1, sizeof(BITMAPFILEHEADER), bmp);//Считываем FILEHEADER
    fread(&bmpInfo, 1, sizeof(BITMAPINFOHEADER), bmp);//Считываем INFOHEADER
    try//Обработка исключения
    {
        if ((bmpHeader.bfType != 0x4D42) || (bmpInfo.biBitCount != 24))//Проверка сигнатуры и глубины цвета
        {
            throw "Файл должен быть 24-х битным .bmp";
        }
    } catch (const char* )//Если файл не того формата - выкидываем исключение...
    {
        return nullptr;
    }
    //const long int dataSize = long int(bmpInfo.biHeight) * bmpInfo.biWidth * 3;
    //const int scanLine = ((bmpInfo.biWidth * 32 + 31) & ~31) / 8 * 3;
    const int additionalPixelsTwo = (bmpInfo.biWidth * 3) % 4 == 0 ? 0 : 4 - (bmpInfo.biWidth * 3) % 4;
    const int scanLine = (bmpInfo.biWidth * 3) + additionalPixelsTwo;
    const long int dataSize = long int(bmpInfo.biHeight) * scanLine;
    unsigned char* data = new unsigned char[dataSize];//Создаем массив для данных о растре
    fseek(bmp, bmpHeader.bfOffBits, SEEK_SET);//Перемещаем указатель в потоке на то место, где начинается инфа оо RGB (Ну так, на всякий случай)
    fread(data, 1, dataSize, bmp);//Данные прочитаны
    fclose(bmp);//Закрываем файл, больше он нам ни к чему


    //for (int i = 0; i < bmpInfo.biHeight; i++) {
    //    for (int j = 0; j < bmpInfo.biWidth / 2; j++) {
    //        swap(data[i * bmpInfo.biWidth + j], data[i * bmpInfo.biWidth + bmpInfo.biWidth - 1 - j]);
    //    }
    //}

    //for (int i = 0; i < int(dataSize / 2); i++) {
    //    swap(data[i], data[(dataSize - 1) - i]);
    //}
    return data;
}

int main() {
    int result = FSDK_ActivateLibrary(key);
    CHECK_IF_FALSE_RETURN(result == FSDKE_OK, "Correct key", "Activation error", 0);

    result = FSDK_Initialize(dllPath);
    CHECK_IF_FALSE_RETURN(result == FSDKE_OK, "Correct initialization of the dll", "Initialization error", 0);

    IFaceFinder* ff = FaceFinder::createFaceFinder();
    ff->init();
    for (int i = 0; i < 7; i++) {
        std::string path = "F:/pic" + std::to_string(i) + ".bmp";
        BITMAPINFOHEADER bmpInfo;
        unsigned char* res = readBmp(path, bmpInfo);
        //Количество добавленных пикселей (в .bmp-шках добавляются в каждую строчку столько пикселей, чтобы их количество было кратно четырем)
        const int additionalPixelsTwo = (bmpInfo.biWidth * 3) % 4 == 0 ? 0 : 4 - (bmpInfo.biWidth * 3) % 4;
        const int scanLine = (bmpInfo.biWidth  * 3 ) + additionalPixelsTwo;
        //const int scanLine = ((bmpInfo.biWidth * 32 + 31) & ~31) / 8 * 3;

        ff->addImage(i, res, bmpInfo.biWidth, bmpInfo.biHeight, scanLine, IFaceFinder::ColorDepth::Bit24);
        delete[]res;
    }
    ff->finish();

    delete ff;

    
    /*
    Для тестирования!

    shared_ptr<HImage> image(new HImage);
    result = FSDK_LoadImageFromFile(image.get(), "F:\\pic.jpg");//!
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(result == FSDKE_OK, "Error in loading process", 0);

    int facesCount = 0;
    shared_ptr<TFacePosition> facePositionPointer(new TFacePosition);
    const int maxSizeInBytes = 1024;
    result = FSDK_DetectMultipleFaces(*image.get(), &facesCount, facePositionPointer.get(), maxSizeInBytes);
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(result == FSDKE_OK, "Error in detecting process", 0);
    CHECK_IF_FALSE(facesCount != 0, 0);
 
    TFacePosition* facePositionArray = facePositionPointer.get();
    for (int i = 0; i < facesCount; i++) {
        FSDK_FaceTemplate* faceTemplate = new FSDK_FaceTemplate;
        result = FSDK_GetFaceTemplateInRegion(*image, &facePositionArray[i], faceTemplate);
        CHECK_IF_FALSE_CONTINUE(result == FSDKE_OK, "Cannot get face template, error code " << result);

        FaceDescription::FaceDescriptionHeader header(0, facePositionArray[i].xc, facePositionArray[i].yc, facePositionArray[i].w, 0, int(sizeof(*faceTemplate)));
        FaceDescription* faceDescription = new FaceDescription(header, faceTemplate->ftemplate[0]);
        FrameRegion* frame = new FrameRegion(1, 1);
        FaceFinder::DescriptionData descriptionData(faceDescription, std::vector<FrameRegion*>() = { frame });
    }
    
    */

    result = FSDK_Finalize();
    CHECK_IF_FALSE_RETURN(result == FSDKE_OK, "Correct finalazing of the dll", "Incorect finalazing... Well... Ok))", 0);

    return 0;
}