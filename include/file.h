#pragma once
#include <bits/stdc++.h>
using namespace std;
class file{
    private:
        static constexpr size_t BUFFER_SIZE = 64*1024;
    public:
    string readfile(string);
    bool create(string);
    string extension(string);
    size_t readChunk(ifstream&, char* , size_t);
    string hashFileContent(string fpath);
    bool checkFileExist(string);
    bool checkExistOrCreate(string );
    bool writeInFile(string , const string&,bool  );
    bool copyContentFromFileToFile(string,string );
    uintmax_t fileSize(string);
    file();
    ~file();
};