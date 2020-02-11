#ifndef _AVI_LOADER_
#define _AVI_LOADER_

#include "atlcomcli.h"
#include "Vfw.h"

#ifdef __INTELLISENSE__
#import "GetAVIInfo.tlh"
#else 
#import "libid:568DF441-DEAC-11D3-BBEE-0000B4908D28" named_guids raw_interfaces_only
#endif

#include <string>

class AviLoader {
public:
    AviLoader();

    AviLoader(const AviLoader& other) = delete;
    AviLoader(AviLoader&& other) noexcept = delete;
    ~AviLoader();
    AviLoader& operator=(const AviLoader& other) = delete;
    AviLoader& operator=(AviLoader&& other) noexcept = delete;

    void init();
    void loadFile(const std::string& path);
    unsigned char* readNextFrame();
    void finish();



private:
    CComPtr <struct GETAVIINFOLib::IGetAVIInfo> avi;
    int totalFrames;
    BITMAPINFO* bmpInfoIn;
    BITMAPINFO bmpInfoOut;
    AVIStreamHeader streamHeader;
    //unsigned char* decodedImage;
    int decodedImageSize;
    int scanLine;
    HIC hic;//codec
    HANDLE myAvi;
    int frameNum;




};

#endif
