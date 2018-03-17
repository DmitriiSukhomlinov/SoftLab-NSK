#include "InputHandlers.h"
#include "LuxandFaceSDK.h"
#include "Settings.h"

#include "Consts.cpp"
#include "Macros.cpp"

int main() {
    //This value is expected to use as a return value for all framework functions 
    int result = -1;

    //Activation of the framework by the key
    result = FSDK_ActivateLibrary(key); 
    CHECK_RETURN(result == FSDKE_OK, "Correct key", "Activation error", 0);

    //Initializing of the .dll library
    result = FSDK_Initialize(dllPath);
    CHECK_RETURN(result == FSDKE_OK, "Correct initialization of the dll",
                                     "Initialization error", 0);

    //Pointer to the library performance of the sample picture
    HImage* image = new HImage;

    //Creatiing the library performance of the sample picture
    result = FSDK_LoadImageFromFile(image, sample1);
    CHECK_RETURN(result == FSDKE_OK, "The sample was successfully loaded",
                                     "Sample loading error", 0);
    CHECK_RETURN(image != nullptr, "Image pointer was created sucsessfully",
                                   "Unexpected behavior, image pointer is null",
                                   0);

    result = Settings::setFaceDetectionParametrs();
    CHECK_PAUSE(result == FSDKE_OK, "The parametrs were setted correctly",
                                    "Error in the face detection parametrs");

    result = Settings::setFaceDetectionThreshold();
    CHECK_PAUSE(result == FSDKE_OK, "The threshold was setted correctly",
                                    "Face detection threshold wasn't setted");


    system("pause");
    return 0;
}