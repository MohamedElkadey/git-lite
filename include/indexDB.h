#pragma once
#include "asset.h"
#include "sqlite3.h"
using namespace std;

class indexDB
{
private:
    /* data */
    const string indexDBPath = getPath(assetsMap.at(Asset::Index));
    const char* indexSQL =
        "CREATE TABLE IF NOT EXISTS tree (id TEXT(128) PRIMARY KEY , path TEXT NOT NULL);";
    const char* insertSQL =
        "INSERT INTO tree (id, path) VALUES (?, ?);";
    const char* selectSQLById =
        "SELECT path FROM tree WHERE id = ?;";
    sqlite3* dbIndex = nullptr;
    string getIndexPaht();
    bool is_open();
    bool open_connection();
public:
    indexDB(/* args */);
    bool setindexDB();
    bool clearIndexDB();
    bool insertFile(string hash,string path );
    string selectById(string id);
    bool exists(string& id);
    ~indexDB();
};
