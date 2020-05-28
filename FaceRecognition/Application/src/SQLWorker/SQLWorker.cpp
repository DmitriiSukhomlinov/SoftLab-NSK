#include "SQLWorker.h"

#include <assert.h>
#include <algorithm>  

#include "../../FaceRecognitionStaticLib/src/FaceFinder/IFaceFinder.h"
#include "../../FaceRecognitionStaticLib/src/Utils/Check.h"
#include "../../FaceRecognitionStaticLib/src/FaceSDK/LuxandFaceSDK.h"

#include "sqlite/sqlite3.h"


const char* SQLWorker::DB_NAME = "my_database.dblite";

const char* SQLWorker::CREATE_VIDEO_TABLE = "CREATE TABLE IF NOT EXISTS Videos(\"index\" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, \"frames_number\" INTEGER, \"path_to_a_video\" STRING);";
const char* SQLWorker::CREATE_FACES_TABLE = "CREATE TABLE IF NOT EXISTS Faces(\"index\" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, \"video_index\" INTEGER, \"face_description\" BLOB);";
//const char* SQLWorker::CREATE_REGIONS_TABLE = "CREATE TABLE IF NOT EXISTS Regions(\"video_index\" INTEGER, \"face_index\" INTEGER, \"regions\" string);";
const char* SQLWorker::CREATE_REGIONS_TABLE = "CREATE TABLE IF NOT EXISTS Regions(\"video_index\" INTEGER, \"face_index\" INTEGER, \"first_frame\" INTEGER, \"duration\" INTEGER);";
const char* SQLWorker::CREATE_SQL = "CREATE TABLE IF NOT EXISTS Faces(\"index\" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, \"video\" STRING, \"face_description\" BLOB, \"regions\" STRING);";

SQLWorker::SQLWorker() : videoId(-1) {

}

int SQLWorker::writeNewVideo(const std::string& pathToVideo, const int framesNumber) {
    sqlite3* db = nullptr;
    int result = sqlite3_open(DB_NAME, &db);
    CHECK_IF_FALSE_RETURN(result == SQLITE_OK, "Databse was opened", sqlite3_errmsg(db), 1);

    char* err = nullptr;
    result = sqlite3_exec(db, CREATE_VIDEO_TABLE, 0, 0, &err);
    CHECK_IF_FALSE_RETURN(result == SQLITE_OK, "Databse processed good", err, 1);

    sqlite3_stmt* stmt = nullptr;
    std::string insertSql = "INSERT INTO Videos(\"index\", \"frames_number\", \"path_to_a_video\") VALUES(NULL, \"" + std::to_string(framesNumber) + "\", \"" + pathToVideo + "\");";
    result = sqlite3_prepare_v2(db, insertSql.c_str(), -1, &stmt, NULL);
    CHECK_IF_FALSE_RETURN(result == SQLITE_OK, "Databse prepared good", "prepare failed: " << sqlite3_errmsg(db), 1);

    result = sqlite3_step(stmt);
    CHECK_IF_FALSE_RETURN(result == SQLITE_DONE, "Databse executed good", "execution failed: " << sqlite3_errmsg(db), 1);

    sqlite3_finalize(stmt);

    videoId = (int)sqlite3_last_insert_rowid(db);
    
    sqlite3_close(db);

    return 0;
}

/*int SQLWorker::writeNewFace(IFaceFinder* faceFinder) {
    sqlite3* db = nullptr;
    int result = sqlite3_open(DB_NAME, &db);
    CHECK_IF_FALSE_RETURN(result == SQLITE_OK, "Databse was opened", sqlite3_errmsg(db), 1);

    char* err = nullptr;
    result = sqlite3_exec(db, CREATE_FACES_TABLE, 0, 0, &err);
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(result == SQLITE_OK, err, 1);
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

        sqlite3_stmt* stmt = nullptr;
        std::string insertSql = "INSERT INTO Faces(\"index\", \"video_index\", \"face_description\") VALUES(NULL, \"" + std::to_string(videoId ) + "\", ?);";
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
}*/

int SQLWorker::writeFaceData(IFaceFinder* faceFinder) {
    sqlite3* db = nullptr;
    int result = sqlite3_open(DB_NAME, &db);
    CHECK_IF_FALSE_RETURN(result == SQLITE_OK, "Databse was opened", sqlite3_errmsg(db), 1);

    char* err = nullptr;
    result = sqlite3_exec(db, CREATE_FACES_TABLE, 0, 0, &err);
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(result == SQLITE_OK, err, 1);

    result = sqlite3_exec(db, CREATE_REGIONS_TABLE, 0, 0, &err);
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(result == SQLITE_OK, err, 1);

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

        sqlite3_stmt* stmt = nullptr;
        std::string insertSql = "INSERT INTO Faces(\"index\", \"video_index\", \"face_description\") VALUES(NULL, \"" + std::to_string(videoId) + "\", ?);";
        result = sqlite3_prepare_v2(db, insertSql.c_str(), -1, &stmt, NULL);
        CHECK_IF_FALSE_RETURN(result == SQLITE_OK, " Faces new line", "prepare failed: " << sqlite3_errmsg(db), 1);

        result = sqlite3_bind_blob(stmt, 1, strData.c_str(), descSize, SQLITE_STATIC);
        CHECK_IF_FALSE_RETURN(result == SQLITE_OK, "Faces bind blob", "prepare failed: " << sqlite3_errmsg(db), 1);

        result = sqlite3_step(stmt);
        CHECK_IF_FALSE_RETURN(result == SQLITE_DONE, "Faces step", "execution failed: " << sqlite3_errmsg(db), 1);

        sqlite3_finalize(stmt);
        const int lastFaceId = (int)sqlite3_last_insert_rowid(db);

        for (int j = 0; j < faceFinder->frameRegionsNum(i); j++) {
            FrameRegion* reg = faceFinder->getFaceRegionByIndex(i, j);
            assert(reg != nullptr);

            stmt = nullptr;
            insertSql = "INSERT INTO Regions(\"video_index\", \"face_index\", \"first_frame\", \"duration\") VALUES(\"" + 
                std::to_string(videoId) + "\", \"" + std::to_string(lastFaceId) + "\", \"" + std::to_string(reg->start) + "\", \"" + std::to_string(reg->duration) + "\");";
            result = sqlite3_prepare_v2(db, insertSql.c_str(), -1, &stmt, NULL);
            CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(result == SQLITE_OK, "prepare failed: " << sqlite3_errmsg(db), 1);

            result = sqlite3_step(stmt);
            CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE((result == SQLITE_DONE), "execution failed: " << sqlite3_errmsg(db), 1);

            sqlite3_finalize(stmt);
        }

    }

    sqlite3_close(db);

    return 0;
}


/*int SQLWorker::writeToSql(IFaceFinder* faceFinder, const std::string& pathToVideo) {
    sqlite3* db = nullptr;
    int result = sqlite3_open(DB_NAME, &db);
    CHECK_IF_FALSE_RETURN(result == SQLITE_OK, "Databse was opened", sqlite3_errmsg(db), 1);

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
}*/

bool SQLWorker::isDatabaseContainsVideo(const std::string& path) const {
    auto regions = getRegionsTableFromDb();
    sqlite3* db = nullptr;
    int result = sqlite3_open(SQLWorker::DB_NAME, &db);
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(result == SQLITE_OK, sqlite3_errmsg(db), false);

    for (const auto& a : regions) {
        std::string sqlGetPathRequest("SELECT path_to_a_video FROM Videos WHERE \"index\" = " + std::to_string(a.videoIndex) + ";");
        sqlite3_stmt* stmt = nullptr;
        result = sqlite3_prepare_v2(db, sqlGetPathRequest.c_str(), -1, &stmt, nullptr);
        CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(result == SQLITE_OK, "prepare failed: " << sqlite3_errmsg(db), 1);

        result = sqlite3_step(stmt);
        CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE((result == SQLITE_ROW), "step failed: " << sqlite3_errmsg(db), 1);

        std::string dbPath = std::string((char*)sqlite3_column_text(stmt, 0));
        sqlite3_finalize(stmt);

        if (dbPath == path) {
            sqlite3_close(db);
            return true;
        }
    }
    sqlite3_close(db);
    return false;
    //return std::find(allPaths.begin(), allPaths.end(), path) != allPaths.end();
}

std::map<double, std::pair<std::string, std::string>, std::greater<double>> SQLWorker::getFacesFromDb(FSDK_FaceTemplate* faceTemplate, const double threshold) {
    auto regions = getRegionsTableFromDb();
    std::map<double, std::pair<std::string, std::string>, std::greater<double>> result;
    sqlite3* db = nullptr;
    int rc = sqlite3_open(SQLWorker::DB_NAME, &db);
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(rc == SQLITE_OK, sqlite3_errmsg(db), result);

    for (const auto& a : regions) {
        std::string sqlGetDescRequest("SELECT face_description FROM Faces WHERE \"index\" = " + std::to_string(a.faceIndex) + ";");
        sqlite3_stmt* stmt = nullptr;
        rc = sqlite3_prepare_v2(db, sqlGetDescRequest.c_str(), -1, &stmt, nullptr);
        CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(rc == SQLITE_OK, "prepare failed: " << sqlite3_errmsg(db), result);

        rc = sqlite3_step(stmt);
        CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE((rc == SQLITE_ROW), "prepare failed: " << sqlite3_errmsg(db), result);

        FaceDescription* desc = reinterpret_cast<FaceDescription*>((char*)sqlite3_column_text(stmt, 0));
        /*FaceDescription* dbDesc = createFaceDescription((int)sizeof(FSDK_FaceTemplate));
        fillFaceDescription(dbDesc, desc->header.frameNumber, desc->header.x, desc->header.y, desc->header.width, desc->header.height, (int)sizeof(*desc->faceTemplate));
        CopyMemory(dbDesc->faceTemplate, desc->faceTemplate, sizeof(FSDK_FaceTemplate));*/
        float similarity = 0.0;
        reinterpret_cast<FSDK_FaceTemplate*>(desc->faceTemplate);
        FSDK_MatchFaces(reinterpret_cast<FSDK_FaceTemplate*>(desc->faceTemplate), faceTemplate, &similarity);
        if (similarity >= threshold) {
            std::string sqlGetPathRequest("SELECT path_to_a_video FROM Videos WHERE \"index\" = " + std::to_string(a.videoIndex) + ";");
            sqlite3_stmt* stmt = nullptr;
            rc = sqlite3_prepare_v2(db, sqlGetPathRequest.c_str(), -1, &stmt, nullptr);
            CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(rc == SQLITE_OK, "prepare failed: " << sqlite3_errmsg(db), result);

            rc = sqlite3_step(stmt);
            CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE((rc == SQLITE_ROW), "step failed: " << sqlite3_errmsg(db), result);

            std::string dbPath = std::string((char*)sqlite3_column_text(stmt, 0));
            sqlite3_finalize(stmt);

            std::string regionsString;
            for (const auto& reg : a.regions) {
                regionsString += std::to_string(reg.first) + "," + std::to_string(reg.second) + ";";
            }

            result[similarity] = { dbPath, regionsString };
        }


        /*FSDK_FaceTemplate* currTemp = reinterpret_cast<FSDK_FaceTemplate*>(a.desc->faceTemplate);
        float similarity = 0.0;
        FSDK_MatchFaces(currTemp, faceTemplate, &similarity);
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
        }*/
    }
    return result;
}

/*static int exec_callback(void* ptr, int argc, char* argv[], char* names[]) {
    sqlite3* db = nullptr;
    int result = sqlite3_open(SQLWorker::DB_NAME, &db);
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(result == SQLITE_OK, sqlite3_errmsg(db), 1);

    std::string sqlGetPathRequest("SELECT path_to_a_video FROM Videos WHERE \"index\" = ");
    sqlGetPathRequest += argv[0];
    sqlGetPathRequest += ";";
    sqlite3_stmt* stmt = nullptr;
    result = sqlite3_prepare_v2(db, sqlGetPathRequest.c_str(), -1, &stmt, nullptr);
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(result == SQLITE_OK, "prepare failed: " << sqlite3_errmsg(db), 1);

    result = sqlite3_step(stmt);
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE((result == SQLITE_ROW), "prepare failed: " << sqlite3_errmsg(db), 1);

    SQLWorker::FaceData data;
    data.path = std::string((char*)sqlite3_column_text(stmt, 0));
    sqlite3_finalize(stmt);

    std::string sqlGetDescRequest("SELECT face_description FROM Faces WHERE \"index\" = ");
    sqlGetDescRequest += argv[1];
    sqlGetDescRequest += ";";
    stmt = nullptr;
    result = sqlite3_prepare_v2(db, sqlGetDescRequest.c_str(), -1, &stmt, nullptr);
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(result == SQLITE_OK, "prepare failed: " << sqlite3_errmsg(db), 1);

    result = sqlite3_step(stmt);
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE((result == SQLITE_ROW), "prepare failed: " << sqlite3_errmsg(db), 1);

    FaceDescription* desc = reinterpret_cast<FaceDescription*>((char*)sqlite3_column_text(stmt, 0));
    data.desc = createFaceDescription((int)sizeof(FSDK_FaceTemplate));
    fillFaceDescription(data.desc, desc->header.frameNumber, desc->header.x, desc->header.y, desc->header.width, desc->header.height, (int)sizeof(*desc->faceTemplate));
    CopyMemory(data.desc->faceTemplate, desc->faceTemplate, sizeof(FSDK_FaceTemplate));

    data.regions = argv[2];
    data.regions += ",";
    data.regions += argv[3];
    data.regions += ";";

    vector<SQLWorker::FaceData>* list = reinterpret_cast<vector<SQLWorker::FaceData>*>(ptr);
    bool exist = false;
    for (auto& a : *list) {
        if (a.desc == data.desc && a.path == data.path) {
            a.regions += data.regions;
            exist = true;
            break;
        }
    }
    if (!exist) {
        list->push_back(data);
    }
    sqlite3_close(db);

    return 0;
}*/

static int exec_callback(void* ptr, int argc, char* argv[], char* names[]) {
    /*sqlite3* db = nullptr;
    int result = sqlite3_open(SQLWorker::DB_NAME, &db);
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(result == SQLITE_OK, sqlite3_errmsg(db), 1);

    std::string sqlGetPathRequest("SELECT path_to_a_video FROM Videos WHERE \"index\" = ");
    sqlGetPathRequest += argv[0];
    sqlGetPathRequest += ";";
    sqlite3_stmt* stmt = nullptr;
    result = sqlite3_prepare_v2(db, sqlGetPathRequest.c_str(), -1, &stmt, nullptr);
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(result == SQLITE_OK, "prepare failed: " << sqlite3_errmsg(db), 1);

    result = sqlite3_step(stmt);
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE((result == SQLITE_ROW), "prepare failed: " << sqlite3_errmsg(db), 1);

    SQLWorker::FaceData data;
    data.path = std::string((char*)sqlite3_column_text(stmt, 0));
    sqlite3_finalize(stmt);

    std::string sqlGetDescRequest("SELECT face_description FROM Faces WHERE \"index\" = ");
    sqlGetDescRequest += argv[1];
    sqlGetDescRequest += ";";
    stmt = nullptr;
    result = sqlite3_prepare_v2(db, sqlGetDescRequest.c_str(), -1, &stmt, nullptr);
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(result == SQLITE_OK, "prepare failed: " << sqlite3_errmsg(db), 1);

    result = sqlite3_step(stmt);
    CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE((result == SQLITE_ROW), "prepare failed: " << sqlite3_errmsg(db), 1);

    FaceDescription* desc = reinterpret_cast<FaceDescription*>((char*)sqlite3_column_text(stmt, 0));
    data.desc = createFaceDescription((int)sizeof(FSDK_FaceTemplate));
    fillFaceDescription(data.desc, desc->header.frameNumber, desc->header.x, desc->header.y, desc->header.width, desc->header.height, (int)sizeof(*desc->faceTemplate));
    CopyMemory(data.desc->faceTemplate, desc->faceTemplate, sizeof(FSDK_FaceTemplate));

    data.regions = argv[2];
    data.regions += ",";
    data.regions += argv[3];
    data.regions += ";";*/

    vector<SQLWorker::DbRegionsTable>* list = reinterpret_cast<vector<SQLWorker::DbRegionsTable>*>(ptr);
    SQLWorker::DbRegionsTable data;
    data.videoIndex = atoi(argv[0]);
    data.faceIndex = atoi(argv[1]);
    std::pair<int, int> region;
    region.first = atoi(argv[2]);
    region.second = atoi(argv[3]);

    bool exist = false;
    for (auto& a : *list) {
        if (a.faceIndex == data.faceIndex && a.videoIndex == data.videoIndex) {
            a.regions.push_back(region);
            std::sort(std::begin(data.regions), std::end(data.regions), [](const std::pair<int, int>& first, const std::pair<int, int>& second) -> bool {
                return first.first > second.first;
            });
            exist = true;
            break;
        }
    }   

    if (!exist) {
        data.regions.push_back(region);
        list->push_back(data);
    }
    //sqlite3_close(db);

    return 0;
}


std::vector<SQLWorker::DbRegionsTable> SQLWorker::getRegionsTableFromDb() const {
    sqlite3* db = nullptr;
    int result = sqlite3_open(DB_NAME, &db);
    CHECK_IF_FALSE_RETURN(result == SQLITE_OK, "Databse was opened", sqlite3_errmsg(db), std::vector<SQLWorker::DbRegionsTable>());

    std::vector<SQLWorker::DbRegionsTable> list;
    char* errmsg = NULL;
    result = sqlite3_exec(db, "SELECT video_index, face_index, first_frame, duration FROM Regions;", exec_callback, &list, &errmsg);
    CHECK_IF_FALSE_RETURN(errmsg == nullptr, "Path list was extracted from database", errmsg, std::vector<SQLWorker::DbRegionsTable>());

    sqlite3_close(db);

    return list;
}

