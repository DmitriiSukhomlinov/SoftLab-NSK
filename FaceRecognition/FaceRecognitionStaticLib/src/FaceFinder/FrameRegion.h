#pragma once

#ifndef _FRAME_REGION_
#define _FRAME_REGION_

//Структура, где будет описано, на каком кадре мы встречаем лицо и сколько кадров этот фрагмент видео длится
struct FrameRegion {
    FrameRegion(const int _start, const int _duration = 1) : start(_start), duration(_duration) {}
    FrameRegion(const FrameRegion& other) : start(other.start), duration(other.duration) {}

    bool operator<(const FrameRegion& other) const {
        return this->start < other.start;
    }

    bool operator==(const FrameRegion& other) const {
        return this->start == other.start && this->duration == other.duration;
    }

    bool intersect(FrameRegion* other) {
        int intersectStart = max(this->start, other->start);
        int intersectEnd = min(this->start + this->duration, other->start + other->duration);
        if (intersectStart > intersectEnd) {
            return false;
        }
        this->start = min(this->start, other->start);
        this->duration = max(this->start + this->duration, other->start + other->duration) - this->start;
        return true;
    }


    int start;
    int duration;
};

#endif // !_FACE_DESCRIPTION_
