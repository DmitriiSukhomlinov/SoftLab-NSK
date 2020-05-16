#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "../../FaceRecognitionStaticLib/src/FaceFinder/IFaceFinder.h"
#include "../../FaceRecognitionStaticLib/src/FaceSDK/LuxandFaceSDK.h"

class SQLWorker {
public:

    int writeToSql(IFaceFinder* faceFinder, const std::string& pathToVideo);
    bool isDatabaseContainsVideo(const std::string& path) const;
    std::unordered_map<std::string, std::string> getFacesFromDb(FSDK_FaceTemplate* faceTemplate, const double threshold);

    struct FaceData {
        std::string path;
        FaceDescription* desc;
        std::string regions;
    };
private:

    std::vector<FaceData> getAllPathsFromDb() const;

    static const char* CREATE_SQL;


};
