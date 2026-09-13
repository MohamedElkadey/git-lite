#pragma once

#include <bits/stdc++.h>
using namespace std;

class Blob{
    private:
        
        static string BlobDirPath ;
    public:

    bool create(string );
    bool exist();
    string read();
    bool write(string);
    Blob();
    ~Blob();
};