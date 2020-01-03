#include "FaceSDK/LuxandFaceSDK.h"
#include "FaceFinder/IFaceFinder.h"
#include "FaceFinder/FaceFinder.h"
#include "Utils/Check.h"
#include "Utils/Consts.h"

#include <iostream>

int main() {

    int result = FSDK_ActivateLibrary(key);
    CHECK_RETURN(result == FSDKE_OK, "Correct key", "Activation error", 0);

    result = FSDK_Initialize(dllPath);
    CHECK_RETURN(result == FSDKE_OK, "Correct initialization of the dll", "Initialization error", 0);
    
    /*
    Для тестирования!

    shared_ptr<HImage> image(new HImage);
    result = FSDK_LoadImageFromFile(image.get(), "F:\\pic.jpg");//!
    CHECK_RETURN_NO_OK_MESSAGE(result == FSDKE_OK, "Error in loading process", 0);

    int facesCount = 0;
    shared_ptr<TFacePosition> facePositionPointer(new TFacePosition);
    const int maxSizeInBytes = 1024;
    result = FSDK_DetectMultipleFaces(*image.get(), &facesCount, facePositionPointer.get(), maxSizeInBytes);
    CHECK_RETURN_NO_OK_MESSAGE(result == FSDKE_OK, "Error in detecting process", 0);
    CHECK(facesCount != 0, 0);
 
    TFacePosition* facePositionArray = facePositionPointer.get();
    for (int i = 0; i < facesCount; i++) {
        FSDK_FaceTemplate* faceTemplate = new FSDK_FaceTemplate;
        result = FSDK_GetFaceTemplateInRegion(*image, &facePositionArray[i], faceTemplate);
        CHECK_CONTINUE(result == FSDKE_OK, "Cannot get face template, error code " << result);

        FaceDescription::FaceDescriptionHeader header(0, facePositionArray[i].xc, facePositionArray[i].yc, facePositionArray[i].w, 0, int(sizeof(*faceTemplate)));
        FaceDescription* faceDescription = new FaceDescription(header, faceTemplate->ftemplate[0]);
        FrameRegion* frame = new FrameRegion(1, 1);
        FaceFinder::DescriptionData descriptionData(faceDescription, std::vector<FrameRegion*>() = { frame });
    }
    
    */


    return 0;
}