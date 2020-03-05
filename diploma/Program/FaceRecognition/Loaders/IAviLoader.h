#pragma once

#include <string>

class ILoader {
public:
    ILoader(const ILoader& other) = default;
    ILoader(ILoader&& other) noexcept = default;
    ~ILoader() = default;
    ILoader& operator=(const ILoader& other) = default;
    ILoader& operator=(ILoader&& other) noexcept = default;

    static ILoader* createLoader();

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
    ILoader() = default;

};
