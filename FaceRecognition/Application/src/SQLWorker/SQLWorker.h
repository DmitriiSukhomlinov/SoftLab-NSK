#pragma once

#include <string>
#include <vector>
#include <map>

#include "../../FaceRecognitionStaticLib/src/FaceFinder/IFaceFinder.h"
#include "../../FaceRecognitionStaticLib/src/FaceSDK/LuxandFaceSDK.h"

class SQLWorker {
public:
    SQLWorker();

    int writeNewVideo(const std::string& pathToVideo, const int framesNumber);
    int writeFaceData(IFaceFinder* faceFinder);

    bool isDatabaseContainsVideo(const std::string& path) const;

    struct FaceFromDbInfo {
        FaceFromDbInfo() : similarity(0.0), bestFrameNumber(0) {}
        double similarity;
        std::string pathToVideo;
        std::string stringRegions;
        int bestFrameNumber;
    };

    std::vector<FaceFromDbInfo> getFacesFromDb(FSDK_FaceTemplate* faceTemplate, const double threshold);


    struct DbRegionsTable {
        int videoIndex;
        int faceIndex;
        std::vector<std::pair<int, int> > regions;
    };

    static const char* DB_NAME;

private:
    std::vector<DbRegionsTable> getRegionsTableFromDb() const;

    int videoId;

    static const char* CREATE_VIDEO_TABLE;
    static const char* CREATE_FACES_TABLE;
    static const char* CREATE_REGIONS_TABLE;


};
