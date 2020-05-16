#include "SQLWorker.h"

#include <assert.h>
#include <algorithm>

#include "../../FaceRecognitionStaticLib/src/FaceFinder/IFaceFinder.h"
#include "../../FaceRecognitionStaticLib/src/Utils/Check.h"
#include "../../FaceRecognitionStaticLib/src/FaceSDK/LuxandFaceSDK.h"

#include "sqlite/sqlite3.h"



const char* SQLWorker::CREATE_SQL = "CREATE TABLE IF NOT EXISTS Faces(\"index\" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, \"video\" STRING, \"face_description\" BLOB, \"regions\" STRING);";

int SQLWorker::writeToSql(IFaceFinder* faceFinder, const std::string& pathToVideo) {
    sqlite3* db = nullptr;
    int result = sqlite3_open("my_database.dblite", &db);
    CHECK_IF_FALSE_RETURN(result == SQLITE_OK, "Databse was created", sqlite3_errmsg(db), 1);

    char* err = nullptr;
    result = sqlite3_exec(db, CREATE_SQL, 0, 0, &err);
    CHECK_IF_FALSE_RETURN(result == SQLITE_OK, "Databse processed good", err, 1);
    for (int i = 0; i < faceFinder->faceCount(); i++) {
        FaceDescription* desc = faceFinder->getFaceInfo(i);
        assert(desc != nullptr);

        const int descSize = sizeof(desc->header) + desc->header.faceTemplateSize;
        char* data = new char[descSize];
        CopyMemory(data, desc, descSize);
        std::string strData;
        for (int j = 0; j < descSize; j++) {
            strData += data[j];
        }
        delete data;

        std::string regions;
        for (int j = 0; j < faceFinder->frameRegionsNum(i); j++) {
            FrameRegion* reg = faceFinder->getFaceRegionByIndex(i, j);
            assert(reg != nullptr);

            regions += std::to_string(reg->start) + "," + std::to_string(reg->duration) + ";";
        }

        sqlite3_stmt* stmt = NULL;
        std::string insertSql = "INSERT INTO Faces(\"index\", \"video\", \"face_description\", \"regions\") VALUES(NULL, \"" + pathToVideo + "\", ?, \"" + regions + "\");";
        result = sqlite3_prepare_v2(db, insertSql.c_str(), -1, &stmt, NULL);
        CHECK_IF_FALSE_RETURN(result == SQLITE_OK, "Databse prepared good", "prepare failed: " << sqlite3_errmsg(db), 1);

        result = sqlite3_bind_blob(stmt, 1, strData.c_str(), descSize, SQLITE_STATIC);
        CHECK_IF_FALSE_RETURN(result == SQLITE_OK, "Databse bind blob is good", "prepare failed: " << sqlite3_errmsg(db), 1);

        result = sqlite3_step(stmt);
        CHECK_IF_FALSE_RETURN(result == SQLITE_DONE, "Databse executed good", "execution failed: " << sqlite3_errmsg(db), 1);

        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);

    return 0;
}

bool SQLWorker::isDatabaseContainsVideo(const std::string& path) const {
    std::vector<SQLWorker::FaceData> allPaths = getAllPathsFromDb();
    for (const auto& a : allPaths) {
        if (a.path == path) {
            return true;
        }
    }
    return false;
    //return std::find(allPaths.begin(), allPaths.end(), path) != allPaths.end();
}

std::unordered_map<std::string, std::string> SQLWorker::getFacesFromDb(FSDK_FaceTemplate* faceTemplate, const double threshold) {
    std::vector<SQLWorker::FaceData> allPaths = getAllPathsFromDb();
    std::unordered_map<std::string, std::string> result;
    for (const auto& a : allPaths) {
        FSDK_FaceTemplate* currTemp = reinterpret_cast<FSDK_FaceTemplate*>(a.desc->faceTemplate);
        float similarity = 0.0;
        /*int result = */FSDK_MatchFaces(currTemp, faceTemplate, &similarity);
        if (similarity >= threshold) {
            std::string foundRegions;
            for (const auto& res : result) {
                if (res.first == a.path) {
                    foundRegions = res.second;
                    break;
                }
            }
            if (!foundRegions.empty()) {
                result[a.path] = foundRegions + a.regions;
            } else {
                result[a.path] = a.regions;
            }
        }
    }
    return result;
}

static int exec_callback(void* ptr, int argc, char* argv[], char* names[]) {
    vector<SQLWorker::FaceData>* list = reinterpret_cast<vector<SQLWorker::FaceData>*>(ptr);
    SQLWorker::FaceData data;
    data.path = argv[0];
    FaceDescription* desc = reinterpret_cast<FaceDescription*>(argv[1]);
    data.desc = createFaceDescription((int)sizeof(FSDK_FaceTemplate));
    fillFaceDescription(data.desc, desc->header.frameNumber, desc->header.x, desc->header.y, desc->header.width, desc->header.height, (int)sizeof(*desc->faceTemplate));
    CopyMemory(data.desc->faceTemplate, desc->faceTemplate, sizeof(FSDK_FaceTemplate));
    //data.desc = new FaceDescription(*desc);
    data.regions = argv[2];
    list->push_back(data);
    return 0;
}

std::vector<SQLWorker::FaceData> SQLWorker::getAllPathsFromDb() const {
    sqlite3* db = nullptr;
    int result = sqlite3_open("my_database.dblite", &db);
    CHECK_IF_FALSE_RETURN(result == SQLITE_OK, "Databse was created", sqlite3_errmsg(db), std::vector<SQLWorker::FaceData>());

    std::vector<SQLWorker::FaceData> list;
    char* errmsg = NULL;
    sqlite3_exec(db, "SELECT video, face_description, regions FROM Faces;", exec_callback, &list, &errmsg);
    CHECK_IF_FALSE_RETURN(errmsg == nullptr, "Path list was extracted from database", errmsg, std::vector<SQLWorker::FaceData>());

    return list;
}

