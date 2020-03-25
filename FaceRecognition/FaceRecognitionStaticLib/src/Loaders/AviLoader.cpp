#include "AviLoader.h"
#include "../Utils/Check.h"
#include "../GetAVIInfo/GetAVIInfo.h"

AviLoader::AviLoader() : avi(nullptr), totalFrames(0), decodedImage(nullptr), decodedImageSize(0), bmpInfoIn(nullptr), scanLine(0), frameNum(-1) {}

AviLoader::~AviLoader() {
    delete bmpInfoIn;
    delete decodedImage;
}

void AviLoader::init() {
    CoInitialize(nullptr);
}

void AviLoader::loadFile(const std::string& path) {
    HRESULT hres = avi.CoCreateInstance(GETAVIINFOLib::CLSID_GetAVIInfo);
    CHECK_IF_FALSE_RETURN(hres == S_OK, "AVI instance was created.", "AVI instaice creatig error.", );

    CComBSTR MyBstr(path.c_str());//convert the format from char to BSTR
    hres = avi->Load(MyBstr);//read AVI file
    CHECK_IF_FALSE_RETURN(hres == S_OK, "AVI file was loaded correctly.", "AVI file loading error.", );

    MainAVIHeader aviHeader;
    long tmp = 0;
    hres = avi->GetMainHeader((unsigned char*)&aviHeader, sizeof(aviHeader), &tmp);//read MainAVIHeader
    CHECK_IF_FALSE_RETURN(hres == S_OK, "Main header was loaded correctly.", "Main header loading error.", );

    totalFrames = aviHeader.dwTotalFrames;
    long sizeBMPINFO = 0;
    hres = avi->GetVideoFormatInfo(0, 0, 0, &sizeBMPINFO);
    CHECK_IF_FALSE_RETURN(hres == S_OK, "Video format info for size was got correctly.", "Video format info for size getting error.", );

    bmpInfoIn = (BITMAPINFO*) new unsigned char[sizeBMPINFO];
    hres = avi->GetVideoFormatInfo(0, (unsigned char*)bmpInfoIn, sizeBMPINFO, &sizeBMPINFO);
    CHECK_IF_FALSE_RETURN(hres == S_OK, "Video format info was got correctly.", "Video format info getting error.", );

    ZeroMemory(&bmpInfoOut, sizeof(bmpInfoOut));
    bmpInfoOut.bmiHeader.biSize = bmpInfoIn->bmiHeader.biSize;
    bmpInfoOut.bmiHeader.biWidth = bmpInfoIn->bmiHeader.biWidth;
    bmpInfoOut.bmiHeader.biHeight = bmpInfoIn->bmiHeader.biHeight;
    bmpInfoOut.bmiHeader.biPlanes = bmpInfoIn->bmiHeader.biPlanes;
    bmpInfoOut.bmiHeader.biBitCount = bmpInfoIn->bmiHeader.biBitCount;

    AVIStreamHeader streamHeader;
    hres = avi->GetVideoStreamInfo(0, (unsigned char*)&streamHeader, sizeof(streamHeader), &tmp, NULL, NULL);
    CHECK_IF_FALSE_RETURN(hres == S_OK, "Video stream info was got correctly.", "Video stream info getting error.", );

    const int additionalPixelsTwo = (bmpInfoIn->bmiHeader.biWidth * 3) % 4 == 0 ? 0 : 4 - (bmpInfoIn->bmiHeader.biWidth * 3) % 4;
    scanLine = (bmpInfoIn->bmiHeader.biWidth * 3) + additionalPixelsTwo;
    decodedImageSize = bmpInfoIn->bmiHeader.biHeight * scanLine;
    decodedImage = new unsigned char[decodedImageSize];
    bmpInfoOut.bmiHeader.biSizeImage = decodedImageSize;

    hic = ICOpen(ICTYPE_VIDEO, streamHeader.fccHandler, ICMODE_DECOMPRESS); //open file for decompression
    if (hic == 0) { //if it didn't work...
        hic = ICLocate(ICTYPE_VIDEO, streamHeader.fccHandler, &bmpInfoIn->bmiHeader, &bmpInfoOut.bmiHeader, ICMODE_DECOMPRESS);//...try to find a codec automatically
    }
    CHECK_IF_FALSE_RETURN(nullptr != hic, "The codec was initialized correctly.", "Can not initialize the codec.", );

    myAvi = CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    CHECK_IF_FALSE_RETURN(myAvi != INVALID_HANDLE_VALUE, "The file was created.", "Can not create file.", );
}

unsigned char* AviLoader::readNextFrame() {
    frameNum++;
    long hiOf = 0;
    unsigned long lowOf = 0;
    unsigned long sizeOfFrame = 0;
    unsigned long key = 0;
    avi->GetVideoFrameInfo2(0, frameNum, &hiOf, &lowOf, &sizeOfFrame, &key);

    //unsigned char* dataIn = new unsigned char[sizeOfFrame];
    shared_ptr<unsigned char> dataIn(new unsigned char[sizeOfFrame]);
    SetFilePointer(myAvi, lowOf, &hiOf, FILE_BEGIN);

    unsigned long bytesWasRead = 0;
    bool wasRead = ReadFile(myAvi, dataIn.get(), sizeOfFrame, &bytesWasRead, NULL);
    CHECK_IF_FALSE(wasRead, nullptr);

    bmpInfoIn->bmiHeader.biSizeImage = sizeOfFrame;
    DWORD res = ICDecompress(hic, key != 16 ? ICDECOMPRESS_NOTKEYFRAME : 0, &bmpInfoIn->bmiHeader, dataIn.get(), &bmpInfoOut.bmiHeader, decodedImage);
   // checkReturn(res);
    CHECK_IF_FALSE(res == ICERR_OK, nullptr);

    return invertPicture(decodedImage);
}

void AviLoader::finish() {
    CoUninitialize();
}

int AviLoader::getSkanLine() const {
    return scanLine;
}

int AviLoader::getPictureWidth() const {
    return bmpInfoOut.bmiHeader.biWidth;
}

int AviLoader::getPictureHeight() const {
    return bmpInfoOut.bmiHeader.biHeight;
}

int AviLoader::getLastReadFrameNumber() const {
    return frameNum;
}

bool AviLoader::hasFrameToRead() const {
    return frameNum != totalFrames - 1;
}

unsigned char* AviLoader::invertPicture(unsigned char* old) {
    unsigned char* invertedData = new unsigned char[decodedImageSize];
    for (int i = 0; i < bmpInfoOut.bmiHeader.biHeight; i++) {
        for (int j = 0; j < bmpInfoOut.bmiHeader.biWidth * 3; j = j + 3) {
            invertedData[i * scanLine + j] = old[(bmpInfoOut.bmiHeader.biHeight - 1 - i) * scanLine + j + 2];
            invertedData[i * scanLine + j + 1] = old[(bmpInfoOut.bmiHeader.biHeight - 1 - i) * scanLine + j + 1];
            invertedData[i * scanLine + j + 2] = old[(bmpInfoOut.bmiHeader.biHeight - 1 - i) * scanLine + j];
        }
    }
    //delete old;

    return invertedData;

}

//void AviLoader::checkReturn(const DWORD& res) const {
//    if (res == ICERR_OK) {
//        int i = 0;
//    } else if (res == ICERR_DONTDRAW) {
//        int i = 0;
//    } else if (res == ICERR_NEWPALETTE) {
//        int i = 0;
//    } else if (res == ICERR_GOTOKEYFRAME) {
//        int i = 0;
//    } else if (res == ICERR_GOTOKEYFRAME) {
//        int i = 0;
//    } else if (res == ICERR_STOPDRAWING) {
//        int i = 0;
//    } else if (res == ICERR_UNSUPPORTED) {
//        int i = 0;
//    } else if (res == ICERR_BADFORMAT) {
//        int i = 0;
//    } else if (res == ICERR_MEMORY) {
//        int i = 0;
//    } else if (res == ICERR_INTERNAL) {
//        int i = 0;
//    } else if (res == ICERR_BADFLAGS) {
//        int i = 0;
//    } else if (res == ICERR_BADPARAM) {
//        int i = 0;
//    } else if (res == ICERR_BADSIZE) {
//        int i = 0;
//    } else if (res == ICERR_BADHANDLE) {
//        int i = 0;
//    } else if (res == ICERR_CANTUPDATE) {
//        int i = 0;
//    } else if (res == ICERR_ABORT) {
//        int i = 0;
//    } else if (res == ICERR_ERROR) {
//        int i = 0;
//    } else if (res == ICERR_BADBITDEPTH) {
//        int i = 0;
//    } else if (res == ICERR_BADIMAGESIZE) {
//        int i = 0;
//    } else if (res == ICERR_CUSTOM) {
//        int i = 0;
//    } else {
//        int i = 0;
//    }
//}
