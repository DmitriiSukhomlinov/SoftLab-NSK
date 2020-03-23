#ifndef _AVI_LOADER_
#define _AVI_LOADER_

#include "ILoader.h"

#include "atlcomcli.h"
#include "Vfw.h"

#ifdef __INTELLISENSE__
#import "GetAVIInfo.tlh"
#else 
#import "libid:568DF441-DEAC-11D3-BBEE-0000B4908D28" named_guids raw_interfaces_only
#endif

#include <string>

class AviLoader : public ILoader {
public:
    AviLoader();

    AviLoader(const AviLoader& other) = delete;
    AviLoader(AviLoader&& other) noexcept = delete;
    ~AviLoader();
    AviLoader& operator=(const AviLoader& other) = delete;
    AviLoader& operator=(AviLoader&& other) noexcept = delete;

    void init() override;
    void loadFile(const std::string& path) override;
    unsigned char* readNextFrame() override;
    void finish() override;


    int getSkanLine() const override;
    int getFrameNumber() const override;
    int getPictureWidth() const override;
    int getPictureHeight() const override;
    int getLastReadFrameNumber() const override;
    bool hasFrameToRead() const override;

private:
    unsigned char* invertPicture(unsigned char* old);
    //void checkReturn(const DWORD& res) const;

    CComPtr <struct GETAVIINFOLib::IGetAVIInfo> avi;
    int totalFrames;
    BITMAPINFO* bmpInfoIn;
    BITMAPINFO bmpInfoOut;
    AVIStreamHeader streamHeader;
    int decodedImageSize;
    unsigned char* decodedImage;
    int scanLine;
    HIC hic;//codec
    HANDLE myAvi;
    int frameNum;

};

#endif
