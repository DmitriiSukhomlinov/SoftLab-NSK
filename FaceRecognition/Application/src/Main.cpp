#define _CRT_SECURE_NO_WARNINGS

#include "atlcomcli.h"

#include "FaceSDK/LuxandFaceSDK.h"
#include "FaceFinder/IFaceFinder.h"
#include "Loaders/IAviLoader.h"
#include "Utils/Check.h"
#include "Utils/Consts.h"

#include <thread>         // std::this_thread::sleep_for
#include <chrono>


//unsigned char* readBmp(const std::string& path, BITMAPINFOHEADER& bmpInfo) {
//    FILE* bmp = fopen(path.c_str(), "rb");//Открываем файл для чтения побитово, НАДО УБРАТЬ ВОРНИНГ!!!
//
//    BITMAPFILEHEADER bmpHeader;
//    fread(&bmpHeader, 1, sizeof(BITMAPFILEHEADER), bmp);//Считываем FILEHEADER
//    fread(&bmpInfo, 1, sizeof(BITMAPINFOHEADER), bmp);//Считываем INFOHEADER
//    try//Обработка исключения
//    {
//        if ((bmpHeader.bfType != 0x4D42) || (bmpInfo.biBitCount != 24))//Проверка сигнатуры и глубины цвета
//        {
//            throw "Файл должен быть 24-х битным .bmp";
//        }
//    } catch (const char* )//Если файл не того формата - выкидываем исключение...
//    {
//        return nullptr;
//    }
//    //const long int dataSize = long int(bmpInfo.biHeight) * bmpInfo.biWidth * 3;
//    //const int scanLine = ((bmpInfo.biWidth * 32 + 31) & ~31) / 8 * 3;
//    const int byteWidth = bmpInfo.biWidth * 3;
//    const int additionalPixelsTwo = (byteWidth) % 4 == 0 ? 0 : 4 - (byteWidth) % 4;
//    const int scanLine = byteWidth + additionalPixelsTwo;
//    const long int dataSize = long int(bmpInfo.biHeight) * scanLine;
//    unsigned char* data = new unsigned char[dataSize];//Создаем массив для данных о растре
//    fseek(bmp, bmpHeader.bfOffBits, SEEK_SET);//Перемещаем указатель в потоке на то место, где начинается инфа оо RGB (Ну так, на всякий случай)
//    fread(data, 1, dataSize, bmp);//Данные прочитаны
//    fclose(bmp);//Закрываем файл, больше он нам ни к чему
//
//    unsigned char* invertedData = new unsigned char[dataSize];
//    for (int i = 0; i < bmpInfo.biHeight; i++) {
//        for (int j = 0; j < byteWidth; j = j + 3) {
//            invertedData[i * scanLine + j] = data[(bmpInfo.biHeight - 1 - i) * scanLine + j + 2];
//            invertedData[i * scanLine + j + 1] = data[(bmpInfo.biHeight - 1 - i) * scanLine + j + 1];
//            invertedData[i * scanLine + j + 2] = data[(bmpInfo.biHeight - 1 - i) * scanLine + j];
//        }
//    }
//    delete[]data;
//    return invertedData;
//}

int main() {
    int result = FSDK_ActivateLibrary(key);
    CHECK_IF_FALSE_RETURN(result == FSDKE_OK, "Correct key", "Activation error", 0);

    result = FSDK_Initialize(dllPath);
    CHECK_IF_FALSE_RETURN(result == FSDKE_OK, "Correct initialization of the dll", "Initialization error", 0);

    ILoader* loader = ILoader::createLoader();
    IFaceFinder* faceFinder = IFaceFinder::createFaceFinder();/////

    loader->init();
    faceFinder->init();

    loader->loadFile("C:/Users/sukho/OneDrive/Desktop/GetAVIInfo/faces2.avi");

    const int width = loader->getPictureWidth();
    const int height = loader->getPictureHeight();
    const int scanLine = loader->getSkanLine();

    while (loader->hasFrameToRead()) {
        unsigned char* data = loader->readNextFrame();
        CHECK_IF_FALSE_CONTINUE_NO_MESSAGE((nullptr != data));

        int curentDataFrameNumber = loader->getLastReadFrameNumber();
        if (curentDataFrameNumber % 100 != 0) {
            //continue;
        }
        faceFinder->addImage(curentDataFrameNumber, data, width, height, scanLine, IFaceFinder::ColorDepth::Bit24);

        delete[] data;
    }
    loader->finish();
    faceFinder->finish();

    delete loader;
    delete faceFinder;
  
    result = FSDK_Finalize();
    CHECK_IF_FALSE_RETURN(result == FSDKE_OK, "Correct finalazing of the dll", "Incorect finalazing... Well... Ok))", 0);

    return 0;
}