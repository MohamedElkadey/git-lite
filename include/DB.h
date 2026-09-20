#pragma once
using namespace std;

class DB
{
private:
    /* data */
    string indexDB;
public:
    DB(/* args */);
    void setindexDB(string path);
    ~DB();
};

DB::DB(/* args */)
{
}

DB::~DB()
{
}
