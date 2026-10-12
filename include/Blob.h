#pragma once

#include <bits/stdc++.h>
using namespace std;

class Blob{
    private:
        
        filesystem::path blobDirPath ;
        string pathByHash(string hash);
    public:

    string create(string filePath);
    string blobExistByHash(string hash);
    bool getFromBlob(string hash , string filePath  );
    Blob();
    ~Blob();
};