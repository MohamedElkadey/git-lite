#include "Blob.h"
#include "file.h"
#include "dir.h"
#include <bits/stdc++.h>
#include <openssl/evp.h>

using namespace std;
namespace fs = filesystem;

Blob::Blob(){}
Blob::~Blob(){}



bool Blob::create(string filePath){
    file fl;
    if(!fl.checkFileExist(filePath)){
        return false;
    }
    string HashFile = fl.hashFileContent(filePath);

    // if(fl.fileSize(filePath)> Config::BUFFER_SIZE ){

    // }

return false;

}


