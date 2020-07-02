#define _CRT_SECURE_NO_WARNINGS

#include "atlcomcli.h"

#include "FaceSDK/LuxandFaceSDK.h"
#include "FaceFinder/IFaceFinder.h"
#include "Loaders/ILoader.h"
#include "Utils/Check.h"
#include "Utils/Consts.h"

#include <iostream>     // std::cout, std::ostream, std::ios
#include <fstream>  
#include <string>
#include <vector>
#include <unordered_map>

#include "assert.h"

#include "SQLWorker/sqlite/sqlite3.h"

#include "SQLWorker/SQLWorker.h"

#include "TimeChecker/TimeChecker.h"

int readBmp(const std::string& path, unsigned char*& data, int& width, int& height, int& scanLine) {
    FILE* bmp = fopen(path.c_str(), "rb");//Открываем файл для чтения побитово, НАДО УБРАТЬ ВОРНИНГ!!!

    BITMAPFILEHEADER bmpHeader;
    BITMAPINFOHEADER bmpInfo;
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
        return 1;
    }
    //const long int dataSize = long int(bmpInfo.biHeight) * bmpInfo.biWidth * 3;
    //const int scanLine = ((bmpInfo.biWidth * 32 + 31) & ~31) / 8 * 3;
    width = bmpInfo.biWidth;
    height = bmpInfo.biHeight;
    const int byteWidth = width * 3;
    const int additionalPixelsTwo = (byteWidth) % 4 == 0 ? 0 : 4 - (byteWidth) % 4;
    scanLine = byteWidth + additionalPixelsTwo;
    const long int dataSize = long int(height) * scanLine;
    data = new unsigned char[dataSize];//Создаем массив для данных о растре
    fseek(bmp, bmpHeader.bfOffBits, SEEK_SET);//Перемещаем указатель в потоке на то место, где начинается инфа оо RGB (Ну так, на всякий случай)
    fread(data, 1, dataSize, bmp);//Данные прочитаны
    fclose(bmp);//Закрываем файл, больше он нам ни к чему

    unsigned char* invertedData = new unsigned char[dataSize];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < byteWidth; j = j + 3) {
            invertedData[i * scanLine + j] = data[(height - 1 - i) * scanLine + j + 2];
            invertedData[i * scanLine + j + 1] = data[(height - 1 - i) * scanLine + j + 1];
            invertedData[i * scanLine + j + 2] = data[(height - 1 - i) * scanLine + j];
        }
    }
    delete[]data;
    data = invertedData;
    return 0;
}

int updateDb(const std::string& path, const double firstThreshold, const double secondThreshold, const int frameMultiplicator) {
    int result = FSDK_ActivateLibrary(key);
    CHECK_IF_FALSE_RETURN(result == FSDKE_OK, "Correct key", "Activation error", 1);

    result = FSDK_Initialize(dllPath);
    CHECK_IF_FALSE_RETURN(result == FSDKE_OK, "Correct initialization of the dll", "Initialization error", 1);

    std::shared_ptr<SQLWorker> sqlWorker(new SQLWorker());
    if (sqlWorker->isDatabaseContainsVideo(path)) {
        std::cout << "The video is already presented in DB";
        return 0;
    }

    std::shared_ptr<ILoader> loader(ILoader::createLoader());
    std::shared_ptr<IFaceFinder> faceFinder(IFaceFinder::createFaceFinder());

    loader->init();
    faceFinder->init(firstThreshold, secondThreshold);

    loader->loadFile(path.c_str());

    const int width = loader->getPictureWidth();
    const int height = loader->getPictureHeight();
    const int scanLine = loader->getSkanLine();

    while (loader->hasFrameToRead()) {
        unsigned char* data = loader->readNextFrame();
        CHECK_IF_FALSE_CONTINUE_NO_MESSAGE((nullptr != data));

        int curentDataFrameNumber = loader->getLastReadFrameNumber();
        if (curentDataFrameNumber % frameMultiplicator != 0) {
            delete[] data;
            continue;
        }
        faceFinder->addImage(curentDataFrameNumber, data, width, height, scanLine, IFaceFinder::ColorDepth::Bit24);

        delete[] data;
    }
    loader->finish();
    faceFinder->finish();

    //FaceDescription* desc = faceFinder->getFaceInfo(5);
    //auto res = sqlWorker->getFacesFromDb(desc, 0.65);

    result = sqlWorker->writeNewVideo(path, loader->getFramesNumber());
    CHECK_IF_FALSE_RETURN(result == FSDKE_OK, "Correct Videos table error", "Videos table error", 1);

    sqlWorker->writeFaceData(faceFinder.get());
    CHECK_IF_FALSE_RETURN(result == FSDKE_OK, "Correct Regions and Faces creation", "Regions and Faces tables error", 1);

    //sqlWorker->writeToSql(faceFinder.get(), path);

    result = FSDK_Finalize();
    CHECK_IF_FALSE_RETURN(result == FSDKE_OK, "Correct finalazing of the dll", "Incorect finalazing... Well... Ok))", 1);

    return 0;
}

int main(int argc, char* argv[]) {
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE((argc > 1), "No arguments, --help to open help", 1);
    if (std::string(argv[1]) == "--help") {
        std::cout
            << "--update path_to_video first_treshold second_treshold [check each 'frame number'] - to update database with a new video;" << endl
            << "--find path_to_picture treshold - to find a person from the picture in the database.";
        return 0;
    } else if (std::string(argv[1]) == "--update") {
        //--update C:/Users/sukho/OneDrive/Desktop/GetAVIInfo/faces2.avi 0.9 0.75
        //--update "F:\softlab-nsk\Test videos\Putin and children questions.avi" 0.9 0.65 100
        CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE((argc == 5 || argc == 6), "Unexpected arguments", 1);
        const std::string pathToVideo = std::string(argv[2]);
        const double firstThreshold = (double)atof(argv[3]) / 100;
        const double secondThreshold = (double)atof(argv[4]) / 100;
        CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE((firstThreshold >= secondThreshold), "Unexpected thresholds, the first must be higher then the second", 1);

        const int frameMultiplicator = argc == 6 ? atoi(argv[5]) : 1;
        return updateDb(pathToVideo, firstThreshold, secondThreshold, frameMultiplicator);
    } else if (std::string(argv[1]) == "--find") {
        CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE((argc == 4), "Unexpected arguments", 1);
        const std::string pathToPicture = std::string(argv[2]);
        const double threshold = (double)atof(argv[3]) / 100;
        int width = -1;
        int height = -1;
        int scanLine = -1;
        unsigned char* data = nullptr;
        int result = readBmp(pathToPicture, data, width, height, scanLine);
        CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(result == 0, "Incorrect input picture", 1);

        result = FSDK_ActivateLibrary(key);
        CHECK_IF_FALSE_RETURN(result == FSDKE_OK, "Correct key", "Activation error", 1);

        result = FSDK_Initialize(dllPath);
        CHECK_IF_FALSE_RETURN(result == FSDKE_OK, "Correct initialization of the dll", "Initialization error", 1);

        HImage image;
        result = FSDK_LoadImageFromBuffer(&image, data, width, height, scanLine, FSDK_IMAGEMODE::FSDK_IMAGE_COLOR_24BIT);//!
        CHECK_IF_FALSE_RETURN(result == FSDKE_OK, "Image loaded from buffer corretly", "Error in the loading process, error code " << result, 1);
        if (result != FSDKE_OK) {
            FSDK_FreeImage(image);
            cout << "Error in the loading process, error code " << result;
            return 1;
        }

        int facesCount = 0;
        shared_ptr<TFacePosition> facePositionPointer(new TFacePosition[10]);
        result = FSDK_DetectMultipleFaces(image, &facesCount, facePositionPointer.get(), sizeof(TFacePosition) * 10);
        if (facesCount == 0) {
            FSDK_FreeImage(image);
            cout << "No faces on picture" << result << endl;
            return 0;
        }else if (facesCount > 1) {
            FSDK_FreeImage(image);
            cout << "Too many faces on picture, please, separate into several pictures" << endl;
            return 0;
        }
        cout << "The only face was found, correct" << endl;

        TFacePosition* facePositionArray = facePositionPointer.get();
        std::shared_ptr<FSDK_FaceTemplate> faceTemplate(new FSDK_FaceTemplate);
        result = FSDK_GetFaceTemplateInRegion(image, &facePositionArray[0], faceTemplate.get());
        CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(result == FSDKE_OK, "Cannot get face template, error code " << result, 1);
        FSDK_FreeImage(image);

        std::shared_ptr<SQLWorker> sqlWorker(new SQLWorker());
        TimeChecker tc;
        tc.startTimer();
        auto res = sqlWorker->getFacesFromDb(faceTemplate.get(), threshold);
        cout << tc.checkTimer() << " Microseconds" << endl;

        std::filebuf fb;
        fb.open("out.txt", std::ios::out);
        std::ostream fout(&fb);
        int i = 1;
        for (const auto& a : res) {
            fout << std::to_string(i++) << "." << endl;
            fout << "Similarity: " << a.similarity << endl;
            fout << "Video: " << a.pathToVideo << endl;
            fout << "Best frame number: " << a.bestFrameNumber << endl;
            fout << "Regions: " << a.stringRegions << endl << endl;

            std::shared_ptr<ILoader> loader(ILoader::createLoader());
            loader->init();
            loader->loadFile(a.pathToVideo);
            const int width = loader->getPictureWidth();
            const int height = loader->getPictureHeight();
            const int scanLine = loader->getSkanLine();
            unsigned char* data = nullptr;
            while (true) {
                data = loader->readNextFrame();
                if (loader->getLastReadFrameNumber() == a.bestFrameNumber) {
                    break;
                } else {
                    delete data;
                }
            }

            HImage image;
            result = FSDK_LoadImageFromBuffer(&image, data, width, height, scanLine, FSDK_IMAGEMODE::FSDK_IMAGE_COLOR_24BIT);//!
            if (result != FSDKE_OK) {
                FSDK_FreeImage(image);
                cout << "Error in the loading process, error code " << result;
                return 1;
            }

            std::string file = std::to_string(i-1) + ".bmp";
            result = FSDK_SaveImageToFile(image, file.c_str());
            FSDK_FreeImage(image);
            loader->finish();
        }
        fb.close();

    } else {
        CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(false, "Unexpected second argument", 1);
    }
}