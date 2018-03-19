#include "InputHandlers.h"
#include "LuxandFaceSDK.h"
#include "Settings.h"
#include "TimeChecker.h"

#include "Consts.cpp"
#include "Macros.cpp"

#include <memory>

int main() {
    //This value is expected to use as a return value for all framework functions 
    int result = -1;
    //This class is intended for the measurement of functions working-time
    TimeChecker time;

    //Activation of the framework by the key
    result = FSDK_ActivateLibrary(key); 
    CHECK_RETURN(result == FSDKE_OK, "Correct key", "Activation error", 0);

    //Initializing of the .dll library
    result = FSDK_Initialize(dllPath);
    CHECK_RETURN(result == FSDKE_OK, "Correct initialization of the dll",
                                     "Initialization error", 0);

    //Pointer to the library performance of the sample picture
    shared_ptr<HImage> image1(new HImage);
    //Creatiing the library performance of the sample picture
    result = FSDK_LoadImageFromFile(image1.get(), sampleMe3);
    CHECK_RETURN(result == FSDKE_OK, "The sample was successfully loaded",
                                     "Sample loading error", 0);
    CHECK_RETURN(image1 != nullptr, "Image pointer was created sucsessfully",
                                   "Unexpected behavior, image pointer is null",
                                   0);

    shared_ptr<HImage> image2(new HImage);
    //Creatiing the library performance of the sample picture
    result = FSDK_LoadImageFromFile(image2.get(), sampleMe4);
    CHECK_RETURN(result == FSDKE_OK, "The sample was successfully loaded",
                                     "Sample loading error", 0);
    CHECK_RETURN(image2 != nullptr, "Image pointer was created sucsessfully",
                                    "Unexpected behavior, image pointer is null",
                                    0);

/*
    //The struct represent 70 points of the face
    FSDK_Features* features = new FSDK_Features[FSDK_FACIAL_FEATURE_COUNT];
    result = FSDK_DetectFacialFeatures(*image1, features);
    CHECK_RETURN(result == FSDKE_OK, "Facial features was defined corectly",
                                     "Facial features weren't setted", 0);

    CHECK_RETURN(features != nullptr, "Facial-features pointer was created sucsessfully",
                                      "Unexpected behavior, Facial-features pointer is null",
                                      0);

    TFacePosition* fasePosition = new TFacePosition;
    time.startTimer("Face Detection"); 
    result = FSDK_DetectFace(*image1, fasePosition);
    time.checkTimer();
    CHECK_RETURN(result == FSDKE_OK, "Face position was defined corectly",
                                     "Face position weren't setted", 0);
    CHECK_RETURN(fasePosition != nullptr, "Face position pointer was created sucsessfully",
                                          "Unexpected behavior, Face position pointer is null",
                                          0); */

    //Library performance of the face
    shared_ptr<FSDK_FaceTemplate> faceTemplate1(new FSDK_FaceTemplate);
    result = FSDK_GetFaceTemplate(*image1, faceTemplate1.get());
    CHECK_RETURN(result == FSDKE_OK, "The Face template was successfully defined",
                                     "Face template definding error", 0);
    CHECK_RETURN(faceTemplate1 != nullptr, "Face template pointer was created sucsessfully",
                                    "Unexpected behavior, face template pointer is null",
                                    0);

    shared_ptr<FSDK_FaceTemplate> faceTemplate2(new FSDK_FaceTemplate);
    result = FSDK_GetFaceTemplate(*image2, faceTemplate2.get());
    CHECK_RETURN(result == FSDKE_OK, "The Face template was successfully defined",
                                     "Face template definding error", 0);
    CHECK_RETURN(faceTemplate2 != nullptr, "Face template pointer was created sucsessfully",
                                    "Unexpected behavior, face template pointer is null",
                                    0);

    //The similarity of two represented faces
    float similarity = -1.0;
    time.startTimer("Face match");
    result = FSDK_MatchFaces(faceTemplate1.get(), faceTemplate2.get(), &similarity);
    time.checkTimer(TimeChecker::Microseconds);
    CHECK_RETURN(result == FSDKE_OK, "Face mutch operation successfull",
                                     "Face mutch operation error", 0);

    cout << "Similarity is " << (int)(similarity * 100) << "%" << endl;
    



    system("pause");
    //delete[] features;
    //delete fasePosition;
    return 0;
}