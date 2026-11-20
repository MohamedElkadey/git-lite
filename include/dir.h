#pragma once

#include <bits/stdc++.h>
using namespace std;
namespace fs = filesystem;


class dir
{
private:
    bool createDirPathR(fs::path&);

public:
    dir(/* args */);
    ~dir();
    bool createDir(string );
    bool dirExist(string);
    bool createDirPath(string);
    bool fileExist(string);
    string currentDir();

};


