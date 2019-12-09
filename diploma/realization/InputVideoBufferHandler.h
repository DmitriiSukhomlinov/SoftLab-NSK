#ifndef _INPUT_VIDEO_BUFFER_HANDLER_
#define _INPUT_VIDEO_BUFFER_HANDLER_

#include <list>

#include "FaceDescription.h"

//Я не совсем понял, что имеется ввиду что "Это должен быть интерфейс"? Интерфейсы сами по себе не имеют реализации - здесь должно быть нечто подобное?
//Или имеется ввиду только конкретно то, что он не должен иметь никаких внешних структур?

class InputVideoBufferHandler {
public:
    //Библиотека FaceSDK имеет собственный enum подобного вида, но я не совсем уверен, стоит ли использовать в нашем коде именно его
    //Возможно, лучше будет завести собственный аналогичный enum и ставить в соответствие нашему значению значение библиотеки
    //Это для того, что бы у нас не "торчал наружу" какой-либо код библиотеки.
    //Поскольку, на данный момент, этот enum выглядит как осообенность данного-конкретного класса InputVideoBufferHandler, я поместил его прямо внутрь класса.
    enum class ColorDepth {
        Bit8,
        Bit24,
        Bit32
    };

    //Конструктор. Предполагаю, что других конструкторов быть не должно.
    //Я предпологал, что это обработчик сразу ВСЕХ картинок и они должны передаваться все разом
    //Как я понял, вся видеозапись превращается в один большой массив данных (некий указатель на "что-то"), 
    //мы принимаем это как void-указатель и делаем dynamic_cast к нужному нам типу данных
    //Возможно, я не совсем правильно понял идею, тогда было бы хорошо, если бы вы еще раз пояснили
    InputVideoBufferHandler(void* _inputVideoBuffer, const int _xPictureSize, const int _yPictureSize, const int _scanLine, const ColorDepth _colorDepth);

    //Перегружаем всякое обязательное добро
    InputVideoBufferHandler(const InputVideoBufferHandler& other);
    InputVideoBufferHandler(InputVideoBufferHandler&& other) noexcept;
    ~InputVideoBufferHandler();
    InputVideoBufferHandler& operator=(const InputVideoBufferHandler& other);
    InputVideoBufferHandler& operator=(InputVideoBufferHandler&& other) noexcept;

    //Функция, стартующая цикл, в котором будут обрабатываться картинка одна за одной
    void init();
    //Функция, завершающая обработку
    void finish();
    //Ну и, соответственно, функция для взятия результата извне
    std::list<FaceDescription> getFaceDescriptions() const;    

private:
    //Входные данные
    void* inputVideoBuffer;
    int xPictureSize;
    int yPictureSize;
    int scanLine;
    ColorDepth colorDepth;
    //А сюда будет сохраняться результат обработки
    std::list<FaceDescription> descriptions;
};

#endif // !_INPUT_VIDEO_BUFFER_HANDLER_
