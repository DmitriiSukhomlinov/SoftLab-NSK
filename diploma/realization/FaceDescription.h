#ifndef _FACE_DESCRIPTION_
#define _FACE_DESCRIPTION_

#include <list>

//Наше описание лица. 
struct FaceDescription {
    struct FaceDescriptionHeader {
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

        //Поля структуры
        PictureWithFace bestPicture;
        //Поскольку одно лицо может встречаться сразу в нескольких не связанных друг с другом фрагментах, нужен лист
        int faceTemplateSize;
    };

    //Структура-структурой, но если мы будем создавать объект с неопределенными полями будет нехорошо, как минимум надо иметь возможность занулить переменные
    FaceDescription();

    //Так же нужно обязательно перегрузить
    FaceDescription(const FaceDescription& other) override;
    FaceDescription(FaceDescription&& other) noexcept override;
    ~FaceDescription() override;
    FaceDescription& operator=(const FaceDescription& other) override;
    FaceDescription& operator=(FaceDescription&& other) noexcept override;


    //Здесь мы храним всю информацию - размер картинки, кадры, и, самое главное - размер Face Template'а
    FaceDescriptionHeader header;
    //Указатель на массив с данными темплейта, размер массива лежит в структуре выше
    char faceTemplate[1];
};


#endif // !_FACE_DESCRIPTION_
