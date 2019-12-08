#ifndef _INPUT_VIDEO_BUFFER_HANDLER_
#define _INPUT_VIDEO_BUFFER_HANDLER_

#include <list>

//“от самый вспомогательный класс, который умеет хранить ошибки
class OperationStatus;
//Ўаблон лица из библиотеки.  стати, он структура, а не класс
struct FSDK_FaceTemplate;
//библиотечный класс, содержащий изображение
class HImage;

//Ќаше описание лица. 
//¬от какой вопрос: должен ли это быть класс, с недоступными напр€мую извне пол€ми, или же структура, открыта€ всем и каждому?
struct/*class*/ FaceDescription {
    //ƒанна€ структура хранит информацию о картинке и местоположении лица на нем
    struct PictureWithFace {
        //указатель на катринку
        HImage* image;
        //ћесто, где находитс€ лицо - координаты угла, ширина и высота
        int x;
        int y;
        int width;
        int height;
    };
    //—труктура, где будет описано, на каком кадре мы встречаем лицо и сколько кадров этот фрагмент видео длитс€
    struct FragmentFrames {
        int start;
        int duration;
    };

    //ѕол€ структуры
    FSDK_FaceTemplate faceTemplate;
    PictureWithFace bestPicture;
    //ѕоскольку одно лицо может встречатьс€ сразу в нескольких не св€занных друг с другом фрагментах, нужен лист
    std::list<FragmentFrames> fragments;
};

class InputVideoBufferHandler {
public:
    //Ѕиблиотека FaceSDK имеет собственный enum подобного вида, но € не совсем уверен, стоит ли использовать в нашем коде именно его
    //¬озможно, лучше будет завести собственный аналогичный enum и ставить в соответствие нашему значению значение библиотеки
    //Ёто дл€ того, что бы у нас не "торчал наружу" какой-либо код библиотеки.
    //ѕоскольку, на данный момент, этот enum выгл€дит как осообенность данного-конкретного класса InputVideoBufferHandler, € поместил его пр€мо внутрь класса.
    enum class ColorDepth {
        Bit8,
        Bit24,
        Bit32
    };

    // онструктор. ѕредполагаю, что других конструкторов быть не должно.
    InputVideoBufferHandler(void* _inputVideoBuffer, const int _xPictureSize, const int _yPictureSize, const int _scanLine, const ColorDepth _colorDepth);

    //ѕерегружаем вс€кое об€зательное добро
    InputVideoBufferHandler(const InputVideoBufferHandler& other);
    InputVideoBufferHandler(InputVideoBufferHandler&& other) noexcept;
    ~InputVideoBufferHandler();
    InputVideoBufferHandler& operator=(const InputVideoBufferHandler& other);
    InputVideoBufferHandler& operator=(InputVideoBufferHandler&& other) noexcept;

    //‘ункци€, стартующа€ цикл, в котором будут обрабатыватьс€ картинка одна за одной
    void init(OperationStatus& os);
    //‘ункци€, завершающа€ обработку
    void finish(OperationStatus& os);
    //Ќу и, соответственно, функци€ дл€ вз€ти€ результата извне
    std::list<FaceDescription> getFaceDescriptions() const;    

private:
    //¬ходные данные
    void* inputVideoBuffer;
    int xPictureSize;
    int yPictureSize;
    int scanLine;
    ColorDepth colorDepth;
    //ј сюда будет сохран€тьс€ результат обработки
    std::list<FaceDescription> descriptions;
};

#endif // !_INPUT_VIDEO_BUFFER_HANDLER_
