#include "file.h"
#include "dir.h"

#include <bits/stdc++.h> // filessystem , fstream 
#include <openssl/sha.h>

using namespace std;
namespace fs = filesystem;

bool file::create(string path){
    fs::path fpath =  fs::path(path);
    
    dir dd;
    if (!dd.createDirPath(fpath.parent_path().string()))
        return false;
    try
    {
        cout<<"try create file "<<path<<'\n';
        ofstream fl(fpath);
        return fl.is_open();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    
}

string file::readfile(string fpath){
    ifstream file(fpath, ios::binary);

    if (!file.is_open()) {
        cerr << "Couldn't open file: " << fpath << '\n';
        return "";
    }

    file.seekg(0, ios::end);
    size_t size = file.tellg();
    file.seekg(0, ios::beg);

    string content;
    content.resize(size);
    file.read(content.data(), size);
    return content;
}

bool file::checkFileExist(string fpath){
    dir dd;
    return dd.fileExist(fs::path(fpath));
}

size_t file::readChunk(ifstream& file,char* buffer,size_t buffer_size ){
    file.read(buffer, buffer_size);
    return static_cast<size_t>(file.gcount());
}

bool file::writeInFile(string fpath, const string& content,bool overWrite){
    if(!checkExistOrCreate(fpath)) return false;

    ios::openmode mode = ios::binary | (overWrite ? ios::trunc : ios::app);
    ofstream out(fpath, mode);
    if (!out) return false;
    out.write(content.data(), (streamsize)content.size());
    out.close();
    return out.good();
}

bool file::copyContentFromFileToFile(string sourceFilePath,string destinationFilePath ){
    if(!checkExistOrCreate(sourceFilePath)) return false;

    ifstream sourceFile(sourceFilePath , ios::binary);
    ofstream destinationFile(destinationFilePath , ios::binary | ios::trunc);
    if(!sourceFile || !destinationFile) return false;
    
    vector<char>buffer(BUFFER_SIZE);
    while (true)
    {
        size_t read = readChunk(sourceFile,buffer.data(),buffer.size());
        if(read == 0) break;
        destinationFile.write(buffer.data(),(streamsize)read);
    }
    sourceFile.close();
    destinationFile.close();
    return destinationFile.good();
}

string file::hashFileContent(string fpath){
    if(!checkFileExist(fpath)){
        cout<<"Couldn\'t find "<<fpath<<'\n';
        return "";
    }
    ifstream file(fpath, ios::binary);
    if(!file.is_open()){
        cout<<"Couldn\'t open file "<<fpath<<'\n';
        return "";
    }
    uint64_t size = fs::file_size(fpath);
    string header = "blob "+ to_string(size)+'\0';
    SHA_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx ,header.data(),header.size());
    vector<char> buffer(BUFFER_SIZE);
    while (true)
    {
        size_t chunk = readChunk(file,buffer.data(),buffer.size());
        if(chunk == 0)
            break;
        SHA1_Update(&ctx ,buffer.data() , chunk);
    }
    unsigned char digest[SHA_DIGEST_LENGTH];
    if(!SHA1_Final(digest, &ctx)){
        cout<<"Couldn\'t het Hash";
        return "";    
    }
    file.close();
    ostringstream oss;
    for (unsigned char byte : digest) {
        oss << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<int>(byte);
    }

    return oss.str();
}

bool file::checkExistOrCreate(string fpath){
    if(!checkFileExist(fpath)){
        if(!create(fpath)){
            cout<<"Couldn\'t create file \n"; 
            return false;
        }
    }
    return true;
}

string file::extension(string fpath){
    fs::path path = fs::path(fpath);
    return path.extension().string();
}

uintmax_t file::fileSize(string fpath){
    try
    {
        fs::path path = fs::path(fpath);
        if(!checkFileExist(fpath))
            return uintmax_t(0);
        return fs::file_size(path);    
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return uintmax_t(0);
    }
}
bool file::clearFile(string path){
    return writeInFile(path ,"",true);
}

file::file(){

}
file::~file(){
    
}