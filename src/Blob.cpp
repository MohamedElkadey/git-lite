#include "Blob.h"
#include "file.h"
#include "dir.h"
#include <bits/stdc++.h>
#include <openssl/evp.h>
#include "myzlib.h"

using namespace std;
namespace fs = filesystem;

Blob::Blob(string objectDir){
    dir dd;
    dd.createDir(objectDir);
    this->blobDirPath = fs::path(objectDir);
}
Blob::~Blob(){}
/*
create file 
    hash file H
    check if hash is in object 
        if not 
        create file as object
        compress it in this file
    return hash
    
chechBlobThere by hash
    if exist of file hash 
getBlob by hash 
    return it from object if there 
getFromBlob from hash 
    chech if file exist 
    decompress it in file path 

*/


string Blob::create(string filePath){
    file fl;
    if(!fl.checkFileExist(filePath)){
        return "";
    }
    string HashFile = fl.hashFileContent(filePath);
    if(!blobExistByHash(HashFile).empty()){
        return HashFile;
    }
    string pth = pathByHash(HashFile);
    if(!fl.checkExistOrCreate(pth)){
        return "";
    }
    myzlib zl;
    ifstream in(filePath, ios::binary);
    ofstream out(pth,  ios::binary | ios::trunc);
    zl.compressFile(in , out , 8);
    out.close();
    in.close();
    return HashFile;
}

string Blob::pathByHash(string hash){
    string prefix = hash.substr(0,2);
    string suffix = hash.substr(2,hash.length());
    return this->blobDirPath.string() + '/' + prefix +'/' + suffix;
}

string Blob::blobExistByHash(string hash){
    string pth = pathByHash(hash);
    file fl;
    if(fl.checkFileExist(pth))
        return pth;
    return "";
}

bool Blob::getFromBlob(string hash , string filePath ){
    myzlib zl;
    string pth = blobExistByHash(hash);
    if(pth.empty())
        return false;

    ifstream in(pth, ios::binary);
    ofstream out(filePath,  ios::binary | ios::trunc);
    zl.decompressFile(in,out);
    in.close();
    out.close();
    return true;
}

