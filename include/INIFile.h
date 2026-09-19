#pragma once
#include <bits/stdc++.h>
using namespace std;
namespace fs = filesystem;
/*
[cluster]
    "key":"type"="value"
*/
class INIFile
{
public:
    struct Field{
        uint32_t start;
        uint32_t length;
    };
    
    struct Key
    {
        Field Posetion;
        string name;
    };
    
    struct Entry{
        Key key;
        Field type;
        Field value;
    };

    struct Read{
        Field cluster ;
        string name;
        vector<Entry> children;
    };

private:
    fs::path filePath;
    const size_t BUFFER_SIZE = 64*1024;
    struct Edit {
        uint32_t start; // included
        uint32_t end;   // excluded
        string replacement;
    };
    vector<Edit>edits ;

    void readFile(fs::path);
    bool createFile(fs::path);
    bool createPath(fs::path );

public:
    INIFile();
    bool init(string);
    ~INIFile();
};

INIFile::INIFile(){}

bool INIFile::init(string filePath){
    fs::path fp = fs::path(filePath); 
    if(!fs::exists(fp)){
        if(!createFile(fp)){
            return false;
        }
    }else{
        // set filePath from file
    }
    this->filePath = fp;
    return true;
}

bool INIFile::createFile(fs::path path){
    if(fs::exists(path))
        return true;

    if(path.parent_path().empty()){
        dir dd;
        if(!dd.createDirPath(path.parent_path().string()) )
            return false;
    }
    fstream file(path);

    return file.is_open();
}


INIFile::~INIFile(){}

void INIFile::readFile(fs::path){
    uint32_t line = 0 ;
}

/*
read file by chunk with return start and end byte
read Cluseter return string and start and end bytes
edit(cluster , key )-> (start , end)for key -> save edit in vector 
    "key":"type"="val"
sort edit with start -> function to overlap to make edit vector

apply edit -> read the file and write the new things in temp file


read line by line 
found [cluster] -> call cluster function 
    go in lines and find children -> by call function line
        line get info from line 
    add each child if there 
when found new cluster add old one to read 
and call cluster again untill finish 
*/
