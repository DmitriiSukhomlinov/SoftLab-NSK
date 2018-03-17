#include "InputHandlers.h"
#include "LuxandFaceSDK.h"
#include "Settings.h"

int Settings::setFaceDetectionParametrs() {
    const bool handleArbitraryRotations = InputHandlers::inputBool(
    "Select true, if the face rotation angle is from -15..15 degrees to -30..30 degrees (low performance). Select false, if the angle is lesser.");
    const bool determineFaceRotationAngle = InputHandlers::inputBool(
    "Select true, if you want to detect the face rotation angle. Select false, if you don't.");
    const int internalResizeWidth = InputHandlers::inputInt(
    "Select expected width of the picture library will work with. Default value is 384");

    //Choose face detection parametrs
    const int result = FSDK_SetFaceDetectionParameters(
                                handleArbitraryRotations,
                                determineFaceRotationAngle,
                                internalResizeWidth);
    return result;
}

int Settings::setFaceDetectionThreshold() {
    const int threshold = InputHandlers::inputInt(
    "Sets a threshold value for face detection. The default value is 5. The lowest possible value is 1.");

    //Choose face detection threshold
    const int result = FSDK_SetFaceDetectionThreshold(threshold);
    return result;
}