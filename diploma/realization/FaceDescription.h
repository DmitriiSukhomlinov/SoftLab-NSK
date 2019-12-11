#ifndef _FACE_DESCRIPTION_
#define _FACE_DESCRIPTION_

#include <list>

//Аналог FSDK_FaceTemplate из библиотеки
using FaceTemplate = char[dataSize];

//Оставлю пока так, как сделать версионность не совсем пока понимаю
static const int dataSize = 1040;

//Наше описание лица. 
struct FaceDescription {
    //Данная структура хранит информацию о картинке и местоположении лица на нем
    struct PictureWithFace {
        //Индекс (или же порядковый номер?) кадра, на котором находится наиболее четкое лицо
        int frameIndex/*frameNumber*/;
        //Место, где находится лицо - координаты угла, ширина и высота
        int x;
        int y;
        int width;
        int height;
    };
    //Структура, где будет описано, на каком кадре мы встречаем лицо и сколько кадров этот фрагмент видео длится
    struct FragmentFrames {
        int start;
        int duration;
    };

    //Поля структуры
    FaceTemplate faceTemplate;
    PictureWithFace bestPicture;
    //Поскольку одно лицо может встречаться сразу в нескольких не связанных друг с другом фрагментах, нужен лист
    std::list<FragmentFrames> fragments;
};


#endif // !_FACE_DESCRIPTION_
