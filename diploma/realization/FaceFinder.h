#ifndef _FACE_FINDER_
#define _FACE_FINDER_

#include <list>
#include <map>

#include "FaceDescription.h"
#include "IFaceFinder.h"

class FaceFinder : public IFaceFinder {
public:
    //Всякое обязательное добро, перегруженное
    FaceFinder(const FaceFinder& other) override;
    FaceFinder(FaceFinder&& other) noexcept override;
    ~FaceFinder() override;
    FaceFinder& operator=(const FaceFinder& other) override;
    FaceFinder& operator=(FaceFinder&& other) noexcept override;

    //Анализ видео кадр за кадром
    //Функция, стартующая цикл, в котором будут обрабатываться картинка одна за одной
    void init() override;
    //Доавляем картинку на обработку в цикле
    void addImage(const int frameNumber, void* _inputVideoBuffer, const int _xPictureSize, const int _yPictureSize, const int _scanLine, const ColorDepth _colorDepth) override;
    //Функция, завершающая обработку
    void finish() override;

    //получить результат
    //Количество лиц, найденных в ходе обработки
    int faceCount() const override;
    //Ролучить лицо по конкретному ролику
    FaceDescription* getFaceInfo(int index) const override;
    //Получить все лица
    std::list<FaceDescription*> getFaceDescriptions() const override;
    
protected:
    //Наш конструктор, который перегружает конструктор интерфейса
    FaceFinder() override;

private:
    //А сюда будет сохраняться результат обработки
    //Мапа содержит индекс и соответствуещее ему лицо
    std::map<int, FaceDescription*> descriptions;
};

#endif // !_FACE_FINDER_
