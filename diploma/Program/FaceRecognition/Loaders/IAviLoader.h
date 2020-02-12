#pragma once

#include <string>

class IAviLoader {
public:
    IAviLoader(const IAviLoader& other) = default;
    IAviLoader(IAviLoader&& other) noexcept = default;
    ~IAviLoader() = default;
    IAviLoader& operator=(const IAviLoader& other) = default;
    IAviLoader& operator=(IAviLoader&& other) noexcept = default;

    static IAviLoader* createAviLoader();

    virtual void init() = 0;
    virtual void loadFile(const std::string& path) = 0;
    virtual unsigned char* readNextFrame() = 0;
    virtual void finish() = 0;

    virtual int getSkanLine() const = 0;
    virtual int getFrameNumber() const = 0;
    virtual int getPictureWidth() const = 0;
    virtual int getPictureHeight() const = 0;
    virtual int getLastReadFrameNumber() const = 0;
    virtual bool hasFrameToRead() const = 0;

protected:
    IAviLoader() = default;

};
