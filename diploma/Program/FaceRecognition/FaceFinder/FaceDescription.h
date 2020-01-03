#pragma once

#ifndef _FACE_DESCRIPTION_
#define _FACE_DESCRIPTION_

#include <list>

//Наше описание лица. 
struct FaceDescription {
    struct FaceDescriptionHeader {
        //Данная структура хранит информацию о картинке и местоположении лица на нем
        FaceDescriptionHeader(const int _frameNumber, const int _x, const int _y, const int _width, const int _height, const int _faceTemplateSize)
            : frameNumber(_frameNumber), x(_x), y(_y), width(_width), height(_height), faceTemplateSize(_faceTemplateSize) {}

        //Номер кадра, на котором находится наиболее четкое лицо
        int frameNumber;
        //Место, где находится лицо - координаты угла, ширина и высота
        int x;
        int y;
        int width;
        int height;
        //размер шаблона, указатель на первый элемент которого хранится в FaceDescription
        int faceTemplateSize;
    };

    //Структура-структурой, но если мы будем создавать объект с неопределенными полями будет нехорошо, как минимум надо иметь возможность занулить переменные
    FaceDescription(const FaceDescriptionHeader _header, const char faceTemplateFirstByte) : header(_header) 
    {
        faceTemplate[0] = faceTemplateFirstByte;
    }
    //Так же нужно обязательно перегрузить 
    //Вообще, не то чтобы обязательно - тут же нет указателей
    /*FaceDescription(const FaceDescription& other);
    FaceDescription(FaceDescription&& other) noexcept;
    ~FaceDescription();
    FaceDescription& operator=(const FaceDescription& other);
    FaceDescription& operator=(FaceDescription&& other) noexcept;*/

    //Здесь мы храним всю информацию - размер картинки, кадры, и, самое главное - размер Face Template'а
    FaceDescriptionHeader header;
    //Указатель на массив с данными темплейта, размер массива лежит в структуре выше
    char faceTemplate[1];
};


#endif // !_FACE_DESCRIPTION_
