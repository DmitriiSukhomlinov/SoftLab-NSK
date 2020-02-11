#include "AviLoader.h"
#include "../Utils/Check.h"

AviLoader::AviLoader() : avi(nullptr), totalFrames(0), /*decodedImage(nullptr),*/ decodedImageSize(0), bmpInfoIn(nullptr), scanLine(0), frameNum(0) {}

AviLoader::~AviLoader() {

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

    hres = avi->GetVideoStreamInfo(0, (unsigned char*)&streamHeader, sizeof(streamHeader), &tmp, NULL, NULL);
    CHECK_IF_FALSE_RETURN(hres == S_OK, "Video stream info was got correctly.", "Video stream info getting error.", );

    int miliSecPerFrame = 1000 * streamHeader.dwScale / streamHeader.dwRate;//milliseconds per frame
    const int additionalPixelsTwo = (bmpInfoIn->bmiHeader.biWidth * 3) % 4 == 0 ? 0 : 4 - (bmpInfoIn->bmiHeader.biWidth * 3) % 4;
    scanLine = (bmpInfoIn->bmiHeader.biWidth * 3) + additionalPixelsTwo;
    decodedImageSize = bmpInfoIn->bmiHeader.biHeight * scanLine;
    //decodedImage = new unsigned char[bmpInfoIn->bmiHeader.biHeight * scanLine];

    //hic = ICOpen(ICTYPE_VIDEO, streamHeader.fccHandler, ICMODE_DECOMPRESS); //open file for decompression
    if (hic == 0) { //if it didn't work...
        //hic = ICLocate(ICTYPE_VIDEO, streamHeader.fccHandler, &bmpInfoIn->bmiHeader, &bmpInfoOut.bmiHeader, ICMODE_DECOMPRESS);//...try to find a codec automatically
    }
    CHECK_IF_FALSE_RETURN(hres == S_OK, "The codec was initialized correctly.", "Can not initialize the codec.", );

    myAvi = CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    CHECK_IF_FALSE_RETURN(myAvi != INVALID_HANDLE_VALUE, "The file was created.", "Can not create file.", );
}

unsigned char* AviLoader::readNextFrame() {
    long hiOf;
    unsigned long lowOf;
    unsigned long sizeOfFrame;
    unsigned long key;
    HRESULT hres = avi->GetVideoFrameInfo2(0, frameNum, &hiOf, &lowOf, &sizeOfFrame, &key);
    CHECK_IF_FALSE(hres == S_OK, nullptr);

    //unsigned char* dataIn = new unsigned char[sizeOfFrame];
    shared_ptr<unsigned char> dataIn(new unsigned char[sizeOfFrame]);
    hres = SetFilePointer(myAvi, lowOf, &hiOf, FILE_BEGIN);
    CHECK_IF_FALSE(hres == S_OK, nullptr);

    unsigned long bytesWasRead = 0;
    hres = ReadFile(myAvi, dataIn.get(), sizeOfFrame, &bytesWasRead, NULL);
    CHECK_IF_FALSE(hres == S_OK, nullptr);

    frameNum++;

    bmpInfoIn->bmiHeader.biSizeImage = sizeOfFrame;
    unsigned char* decodedImage = new unsigned char[decodedImageSize];
    hres = ICDecompress(hic, key == 0 ? ICDECOMPRESS_NOTKEYFRAME : 0, &bmpInfoIn->bmiHeader, dataIn.get(), &bmpInfoOut.bmiHeader, decodedImage);
    CHECK_IF_FALSE(hres == S_OK, nullptr);

    return decodedImage;
}

void AviLoader::finish() {
    CoUninitialize();
}