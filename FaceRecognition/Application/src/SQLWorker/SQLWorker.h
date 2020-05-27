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
    //int writeNewFace(IFaceFinder* faceFinder);
    int writeFaceData(IFaceFinder* faceFinder);

    //int writeToSql(IFaceFinder* faceFinder, const std::string& pathToVideo);
    bool isDatabaseContainsVideo(const std::string& path) const;
    std::map<double, std::pair<std::string, std::string>> getFacesFromDb(FSDK_FaceTemplate* faceTemplate, const double threshold);

    //struct FaceData {
    //    /*std::string path;
    //    FaceDescription* desc;
    //    std::string regions;*/

    //    int videoIndex;
    //    int faceIndex;
    //    std::list<std::pair<int, int> > regions;
    //};

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
    static const char* CREATE_SQL;


};
