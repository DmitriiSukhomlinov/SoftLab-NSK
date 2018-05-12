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

    //result = Settings::setFaceDetectionParametrs();
    //CHECK_PAUSE(result == FSDKE_OK, "The parametrs were setted correctly",
    //                                "Error in the face detection parametrs");
    //
    //result = Settings::setFaceDetectionThreshold();
    //CHECK_PAUSE(result == FSDKE_OK, "The threshold was setted correctly",
    //                                "Face detection threshold wasn't setted");

    //result = FSDK_SetFaceDetectionParameters(false, false, 256);
    //CHECK_PAUSE(result == FSDKE_OK, "The parametrs were setted correctly",
    //                                "Error in the face detection parametrs");

    
    /*
    shared_ptr<HImage> image1(new HImage);
    result = FSDK_LoadImageFromFile(image1.get(), resolutionTestFirstPic);

    shared_ptr<FSDK_FaceTemplate> faceTemplate1(new FSDK_FaceTemplate);
    result = FSDK_GetFaceTemplate(*image1, faceTemplate1.get());


    shared_ptr<HImage> image2(new HImage);
    result = FSDK_LoadImageFromFile(image2.get(), resolutionTestSecondPic);

    shared_ptr<FSDK_FaceTemplate> faceTemplate2(new FSDK_FaceTemplate);
    result = FSDK_GetFaceTemplate(*image2, faceTemplate2.get());


    float similarity = -1.0;
    result = FSDK_MatchFaces(faceTemplate1.get(), faceTemplate2.get(), &similarity);
    cout << "Similarity of samples is " << similarity << endl;

    cout << endl;

    for (int i = 0; i < 10; i++) {
        shared_ptr<HImage> imagePic(new HImage);
        result = FSDK_LoadImageFromFile(imagePic.get(), resolutionTestSecondGood[i]);

        shared_ptr<FSDK_FaceTemplate> faceTemplatePic(new FSDK_FaceTemplate);
        result = FSDK_GetFaceTemplate(*imagePic, faceTemplatePic.get());

        result = FSDK_MatchFaces(faceTemplate1.get(), faceTemplatePic.get(), &similarity);
        cout << "Similarity of sample and good " << i + 1 << " is " << similarity << endl;
    }

    cout << endl;

    for (int i = 0; i < 10; i++) {
        shared_ptr<HImage> imagePic(new HImage);
        result = FSDK_LoadImageFromFile(imagePic.get(), resolutionTestSecondMid[i]);

        shared_ptr<FSDK_FaceTemplate> faceTemplatePic(new FSDK_FaceTemplate);
        result = FSDK_GetFaceTemplate(*imagePic, faceTemplatePic.get());

        result = FSDK_MatchFaces(faceTemplate1.get(), faceTemplatePic.get(), &similarity);
        cout << "Similarity of sample and mid " << i + 1 << " is " << similarity << endl;
    }

    cout << endl;

    for (int i = 0; i < 10; i++) {
        shared_ptr<HImage> imagePic(new HImage);
        result = FSDK_LoadImageFromFile(imagePic.get(), resolutionTestSecondLow[i]);

        shared_ptr<FSDK_FaceTemplate> faceTemplatePic(new FSDK_FaceTemplate);
        result = FSDK_GetFaceTemplate(*imagePic, faceTemplatePic.get());

        result = FSDK_MatchFaces(faceTemplate1.get(), faceTemplatePic.get(), &similarity);
        cout << "Similarity of sample and low " << i + 1 << " is " << similarity << endl;
    }

    cout << endl;

    system("pause");
    return 0;

    */

    long long resultMatchTime = 0;
    long long resultLoadTime = 0;
    long long resultTemplateTime = 0;
    TimeChecker checker;
    TimeChecker checkerForLoop;
    int res = 0;
    checkerForLoop.startTimer("Loop");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {

            //checker.startTimer("Load first image");
            shared_ptr<HImage> image1(new HImage);
            result = FSDK_LoadImageFromFile(image1.get(), samplePaulWalker[i]);
            cout << i + 1 << ". ";
            //resultLoadTime += checker.checkTimer(TimeChecker::Milliseconds);

            //checker.startTimer("Get first face template");
            shared_ptr<FSDK_FaceTemplate> faceTemplate1(new FSDK_FaceTemplate);
            result = FSDK_GetFaceTemplate(*image1, faceTemplate1.get());
            //resultTemplateTime += checker.checkTimer(TimeChecker::Milliseconds);

            //checker.startTimer("Load second image");
            shared_ptr<HImage> image2(new HImage);
            result = FSDK_LoadImageFromFile(image2.get(), samplePaulWalker[j]);
            //resultLoadTime += checker.checkTimer(TimeChecker::Milliseconds);
            
            //checker.startTimer("Get second face template");
            shared_ptr<FSDK_FaceTemplate> faceTemplate2(new FSDK_FaceTemplate);
            result = FSDK_GetFaceTemplate(*image2, faceTemplate2.get());
            //resultTemplateTime += checker.checkTimer(TimeChecker::Milliseconds);

            checker.startTimer("Match faces");
            float similarity = -1.0;
            result = FSDK_MatchFaces(faceTemplate1.get(), faceTemplate2.get(), &similarity);
            resultMatchTime += checker.checkTimer(TimeChecker::Microseconds);

            if (similarity > 0.6) {
                res++;
            }
            //cout << "Similarity of " << i + 1 << " and " << j + 1 << " is " << similarity << endl;
            //cout << endl;
        }
        cout << endl;
    }
    checkerForLoop.checkTimer(TimeChecker::Seconds);
    //cout << "Result load time " << resultLoadTime << " milliseconds" << endl;
    //cout << "Result template time in average " << resultTemplateTime / 200 << " milliseconds" << endl;
    //cout << res << endl;
    cout << "Result match time in average " << resultMatchTime / 100 << " microseconds" << endl;
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


    //The similarity of two represented faces
    //float similarity = -1.0;
    //time.startTimer("Face match");
    //result = FSDK_MatchFaces(faceTemplate1.get(), faceTemplate2.get(), &similarity);
    //time.checkTimer(TimeChecker::Microseconds);
    //CHECK_RETURN(result == FSDKE_OK, "Face mutch operation successfull",
    //                                 "Face mutch operation error", 0);
    //cout << "Similarity is " << (int)(similarity * 100) << "%" << endl;
    



    system("pause");
    return 0;
}