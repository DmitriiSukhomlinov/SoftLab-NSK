#pragma once

#ifndef _FRAME_REGION_
#define _FRAME_REGION_

//Структура, где будет описано, на каком кадре мы встречаем лицо и сколько кадров этот фрагмент видео длится
struct FrameRegion {
    FrameRegion(const int _start, const int _duration = 1) : start(_start), duration(_duration) {}

    int start;
    int duration;
};

#endif // !_FACE_DESCRIPTION_
