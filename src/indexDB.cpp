#include "lib.h"
#include "indexDB.h"
#include "config.h"
#include "sqlite3.h"

using namespace std;
string indexDB::getIndexPaht(){
    return indexDBPath;
}

bool indexDB::setindexDB(){    
    if(!is_open())
        return false;
    char* error = nullptr;
    if(sqlite3_exec(dbIndex ,indexSQL,nullptr,nullptr ,&error ) != SQLITE_OK){
        cout<<error<<"\n";
        sqlite3_free(error);
        return false;
    }
    return true;
}

bool indexDB::clearIndexDB(){
    return fl.clearFile(getIndexPaht());
}

bool indexDB::insertFile(string hash,string path ){
    if(!is_open())
        return false;
    
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(dbIndex, insertSQL, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_text(stmt, 1, hash.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, path.c_str(),-1,SQLITE_TRANSIENT);
    bool success = sqlite3_step(stmt) == SQLITE_DONE;

    sqlite3_finalize(stmt);

    return success;
}

string indexDB::selectById(string id){
    sqlite3_stmt* stmt = nullptr;
    if(!is_open())
            return "";

    if (sqlite3_prepare_v2(dbIndex, selectSQLById, -1, &stmt, nullptr) != SQLITE_OK)
        return "";

    sqlite3_bind_text(stmt, 1, id.c_str(),-1 ,SQLITE_TRANSIENT);

    string path ="";

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* value = sqlite3_column_text(stmt, 0);

        if (value)
            path = reinterpret_cast<const char*>(value);
    }

    sqlite3_finalize(stmt);
    return path;
}

bool indexDB::exists(string& id)
{
    const char* sql =
        "SELECT 1 FROM tree WHERE id = ? LIMIT 1;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(dbIndex, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_text(stmt, 1, id.c_str(), -1, SQLITE_TRANSIENT);

    bool found = sqlite3_step(stmt) == SQLITE_ROW;

    sqlite3_finalize(stmt);

    return found;
}



bool indexDB::is_open(){
    return dbIndex != nullptr;
}
bool indexDB::open_connection(){
    if( !fl.checkExistOrCreate(getIndexPaht()))
        return false;
    return sqlite3_open(getIndexPaht().data(),&dbIndex) == SQLITE_OK;
}
indexDB::indexDB(/* args */){
    if(!open_connection()){
        sqlite3_close(dbIndex);
        dbIndex = nullptr;
    }
}

indexDB::~indexDB(){
    sqlite3_close(dbIndex);
    dbIndex = nullptr;
}
