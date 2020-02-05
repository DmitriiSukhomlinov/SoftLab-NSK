#pragma once

#ifndef _FACE_FINDER_
#define _FACE_FINDER_

#include <vector>
#include <map>

#include "FaceDescription.h"
#include "IFaceFinder.h"

#include "..\FaceSDK\LuxandFaceSDK.h"

class FaceFinder : public IFaceFinder {
public:
    //Всякое обязательное добро, перегруженное
    FaceFinder(const FaceFinder& other) = delete;
    FaceFinder(FaceFinder&& other) noexcept = delete;
    ~FaceFinder() override;
    FaceFinder& operator=(const FaceFinder& other) = delete;
    FaceFinder& operator=(FaceFinder&& other) noexcept = delete;

    //Анализ видео кадр за кадром
    //Функция, стартующая цикл, в котором будут обрабатываться картинка одна за одной
    void init() override;
    //Доавляем картинку на обработку в цикле
    void addImage(const int frameNumber, void* _inputVideoBuffer, const int _xPictureSize, const int _yPictureSize, const int _scanLine, const ColorDepth _colorDepth) override;
    //void addImage(const int frameNumber, const std::string& path) override;
    //Функция, завершающая обработку
    void finish() override;

    //получить результат
    //Количество лиц, найденных в ходе обработки
    int faceCount() const override;
    //Получить лицо по конкретному ролику
    FaceDescription* getFaceInfo(int index) const override;
    //Возьмем количество регионов, в которых встречается это лицо
    int frameRegionsNum(int index) const override;
    //Получить регион, где встречается это лицо. Если регионов несколько, то по-умолчанию берется первый
    FrameRegion* getFaceRegionByIndex(int index, int frameNum = 0) const override;

    //Наш конструктор, который перегружает конструктор интерфейса
    FaceFinder();




    //Нам нужно хранить мапу, у которой ключом будет индекс, а значением пара, с первым значением FaceDescription, а вторым - лист FrameRegion'ов, где он содержится
    //То есть выглядеть это будет как-то так:
    //std::map<int, std::pair<FaceDescription*, std::list<FrameRegion*> > >
    //Получается ну очень большое нагромождение, что не есть хорошо
    //Поэтому, полагаю, что проще вынести все это добро в особую структуру
private:
    struct DescriptionData {
        //Конструктор. Другие, полагаю, не нужны
        DescriptionData(FaceDescription* _faceDescrition, const std::vector<FrameRegion*>& _frameRegions);
        //Каждый экземпляр этой структуры должен быть уникален
        //То есть у нас нет причин иметь два абсолютно одинаковых экземпляра, с одинаковыми индексами
        //Эта структура - это просто некоторое удобное представление всего, что мы имеем
        //Поэтому, операции присваивания-копирования, я полагаю, надо запретить
        DescriptionData(const DescriptionData& other) = delete;
        DescriptionData(DescriptionData&& other) noexcept = delete;
        ~DescriptionData();
        DescriptionData& operator=(const DescriptionData& other) = delete;
        DescriptionData& operator=(DescriptionData&& other) noexcept = delete;

        FaceDescription* faceDescrition;
        std::vector<FrameRegion*> frameRegions;
    };

    struct FaceDescriptionTemp {
        FaceDescriptionTemp();
        FaceDescriptionTemp(const int bestFrame, TFacePosition* facePosition, FSDK_FaceTemplate* faceTemplate);

        FaceDescriptionTemp(const FaceDescriptionTemp& other) = delete;
        FaceDescriptionTemp(FaceDescriptionTemp&& other) noexcept = delete;
        ~FaceDescriptionTemp();
        FaceDescriptionTemp& operator=(const FaceDescriptionTemp& other) = delete;
        FaceDescriptionTemp& operator=(FaceDescriptionTemp&& other) noexcept = delete;

        void clear();

        int bestFrame;
        std::vector<FrameRegion*> frameRegions;
        TFacePosition* facePosition;
        FSDK_FaceTemplate* faceTemplate;
    };

    bool isNewFaceBetter() const;
    void clearDescriptions();
    void clearTempDescriptions();
    void clearAll();

    //Конечная информация - заполняется при вызове finish
    std::vector<DescriptionData*> descriptions;
    //С этим вектором идет работа во время добавления кадров
    std::vector<FaceDescriptionTemp*> tempDescriptions;

    static const std::map<ColorDepth, FSDK_IMAGEMODE> COLOR_DEPTH_CORRELATION;
    static const double SIMILARITY_THRESHOLD;
    static const int MAX_FACE_COUNT;
};

#endif // !_FACE_FINDER_
