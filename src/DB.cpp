#include <bits/stdc++.h>
#include "DB.h"
#include "file.h"
#include "path_utils.h"
#include "config.h"
#include "sqlite3.h"
#include "gitstructure.h"
using namespace std;
string getIndexPaht(){
    
}


bool DB::setindexDB(string path){
    file fl;
    if( !fl.checkExistOrCreate(path))
        return false;
    sqlite3* db = nullptr;
    if(sqlite3_open(path.data() , &db) != SQLITE_OK)
        return false;
    char* error = nullptr;
    if(sqlite3_exec(db ,indexSQL,nullptr,nullptr ,&error ) != SQLITE_OK){
        cout<<error<<"\n";
        sqlite3_free(error);
        return false;
    }
    sqlite3_close(db);
    indexDB = path;
    return true;
}
bool DB::clearIndexDB(){
    file fl;
    return fl.clearFile(indexDB);
}
// bool insertIndexDB(string path , )


DB::DB(/* args */)
{
}

DB::~DB()
{
}
