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

	shared_ptr<HTracker> tracker(new HTracker);
	result = FSDK_CreateTracker(tracker.get());
	CHECK_RETURN(result == FSDKE_OK, "Tracker was created",
									 "Tracker was not created", 0);

    const char * parametrs = "HandleArbitraryRotations=false[;DetermineFaceRotationAngle=false[;InternalResizeWidth=256]]";
    int errorPosition = -1;
    result = FSDK_SetTrackerMultipleParameters(*tracker.get(), parametrs, &errorPosition);
    CHECK_RETURN(result == FSDKE_OK, "Tracker parametrs was setted correctly",
                                     "Tracker parametrs was setted incorrectly", 0);



    //result = Settings::setFaceDetectionParametrs();
    //CHECK_PAUSE(result == FSDKE_OK, "The parametrs were setted correctly",
    //                                "Error in the face detection parametrs");
    //
    //result = Settings::setFaceDetectionThreshold();
    //CHECK_PAUSE(result == FSDKE_OK, "The threshold was setted correctly",
    //                                "Face detection threshold wasn't setted");

    result = FSDK_SetFaceDetectionParameters(false, false, 384);
    //CHECK_PAUSE(result == FSDKE_OK, "The parametrs were setted correctly",
    //                                "Error in the face detection parametrs");
    long long resultTime = 0;
    TimeChecker checker;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {

            //checker.startTimer("Load first image");
            shared_ptr<HImage> image1(new HImage);
            result = FSDK_LoadImageFromFile(image1.get(), samplePaulWalker[i]);
            //checker.checkTimer(TimeChecker::Milliseconds);

            //checker.startTimer("Get first face template");
            shared_ptr<FSDK_FaceTemplate> faceTemplate1(new FSDK_FaceTemplate);
            result = FSDK_GetFaceTemplate(*image1, faceTemplate1.get());
            //checker.checkTimer(TimeChecker::Milliseconds);

            if (result != 0) {
                int qwe = 0;
            }

            //checker.startTimer("Load second image");
            shared_ptr<HImage> image2(new HImage);
            result = FSDK_LoadImageFromFile(image2.get(), samplePaulWalker[j]);
            //checker.checkTimer(TimeChecker::Milliseconds);

            //checker.startTimer("Get second face template");
            shared_ptr<FSDK_FaceTemplate> faceTemplate2(new FSDK_FaceTemplate);
            result = FSDK_GetFaceTemplate(*image2, faceTemplate2.get());
            //checker.checkTimer(TimeChecker::Milliseconds);
            if (result != 0) {
                int qwe = 0;
            }

            checker.startTimer("Match faces");
            float similarity = -1.0;
            result = FSDK_MatchFaces(faceTemplate1.get(), faceTemplate2.get(), &similarity);
            resultTime += checker.checkTimer(TimeChecker::Microseconds);

            
            cout << "Similarity of " << i + 1 << " and " << j + 1 << " is " << similarity << endl;
            //cout << endl;
        }
        //cout << endl << endl;
    }
    
    cout << "Result time " << resultTime << " microseconds" << endl;
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