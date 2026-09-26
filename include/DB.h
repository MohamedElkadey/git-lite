#pragma once
using namespace std;

class DB
{
private:
    /* data */
    string indexDB;
    const char* indexSQL =
        "CREATE TABLE IF NOT EXISTS tree (id TEXT(128) PRIMARY KEY , path TEXT NOT NULL);";

public:
    DB(/* args */);
    bool setindexDB(string path);
    bool clearIndexDB();
    ~DB();
};
