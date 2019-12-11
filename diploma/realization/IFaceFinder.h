#include "FaceDescription.h"

//Создаем интерфейс, который будет базовым для класса-обработчика видео
class IFaceFinder {
public:
    //Библиотека FaceSDK имеет собственный enum подобного вида, но я не совсем уверен, стоит ли использовать в нашем коде именно его
    //Возможно, лучше будет завести собственный аналогичный enum и ставить в соответствие нашему значению значение библиотеки
    //Это для того, что бы у нас не "торчал наружу" какой-либо код библиотеки.
    //Поскольку, на данный момент, этот enum выглядит как осообенность данного-конкретного класса FaceFinder, я поместил его прямо внутрь класса.
    enum class ColorDepth {
        Bit8,
        Bit24,
        Bit32
    };

    //Опять таки - всякое обязательное добро
    virtual IFaceFinder(const IFaceFinder& other) = default;
    virtual IFaceFinder(IFaceFinder&& other) noexcept = default;
    virtual ~IFaceFinder() = default;
    virtual IFaceFinder& operator=(const IFaceFinder& other) = 0;
    virtual IFaceFinder& operator=(IFaceFinder&& other) noexcept = 0;

    //Данная функция создает экземпляр класса, отнаследованного от данного абстрактного класса
    static IFaceFinder* createFaceFinder();

    //Анализ видео кадр за кадром
    //Инициализируем начало обработки видео
    virtual void init() = 0;
    //Добавляем картинку - буфер данных, размер, scanLine и глубину цвета
    //Эта функция должна вызываться в цикле
    virtual void addImage(void* _inputVideoBuffer, const int _xPictureSize, const int _yPictureSize, const int _scanLine, const ColorDepth _colorDepth) = 0;
    //Заканчиваем обработку данных
    virtual void finish() = 0;

    //получить результат
    //Количество лиц, найденных в ходе обработки
    virtual int faceCount() const = 0;
    //Ролучить лицо по конкретному ролику
    virtual FaceDescription* getFaceInfo(int index) const = 0;
    //Получить все лица
    virtual std::list<FaceDescription*> getFaceDescriptions() const = 0;

protected:
    //Чтобы конструктор нельзя было вызвать извне, помещаем его в зону protected
    virtual IFaceFinder() = default;

}
