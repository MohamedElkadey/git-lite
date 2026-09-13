#include "gitstructure.h"
#include "dir.h"
#include "file.h"
#include <bits/stdc++.h>


using namespace std; 
static dir dd;

void gitstructure::init(){
    if (!findRepositoryRoot().empty()) {
        std::cout << "Already inside a repository.\n";
        return;
    }

    auto root = fs::current_path();
    this->path = root.string();

    if (!dd.dirExist(getDir())) {
        dd.createDir(getDir());
    }
    
    for( auto& info : assets){
        int problems = checkasset(info.asset);

        if (problems) {
            cout << info.name << " has problems\n";
            createasset(info.asset);
        }
    }
}
string gitstructure::findRepositoryRoot() {
    fs::path current = fs::current_path();

    while (true) {
        if (fs::exists(current / this->gtDir)) {
            return current.string();
        }

        if (current == current.parent_path()) {
            break;
        }

        current = current.parent_path();
    }

    return "";
}


bool gitstructure::creategitDir(){
    return dd.createDirPath(this->gtDir );
}

bool gitstructure::createasset(Asset asset)
{
    const auto& info = getInfo(asset);
    const string path = getPath(asset);

    if (info.type == AssetType::Directory) {
        return dd.createDirPath(path);
    }
    if(info.asset == Asset::Config){
        
        // if(!Config::setRootPath(this->path , getDir() +'/'+info.name))
        //     return false;
    }

    file f;
    return f.create(path);
}

string gitstructure::getPath(Asset asset) const{
    const auto& info = getInfo(asset);
    return getDir() + '/' + info.name;
}

string gitstructure::getDir()const { 
    return this->path +'/' +this->gtDir; 
}



bool gitstructure::havegitDir(){
    return dd.dirExist(this->getDir());
}



int gitstructure::checkasset(Asset asset)
{
    const auto& info = getInfo(asset);
    const string path = getPath(asset);

    if (info.type == AssetType::Directory) {
        return !dd.dirExist(path);
    }

    return !dd.fileExist(path) ;
}

int gitstructure::setbit(int value, int pos) {
    return value | (int)(1u << pos);
}

const gitstructure::AssetInfo& gitstructure::getInfo(Asset asset) const{
    for(auto& info : assets ){
        if(info.asset == asset){
            return info;
        }
    }
    throw runtime_error("Unknown asset");
}



bool getbit(int x, int pos) {
    return (x & static_cast<int>(1u << pos)) != 0;
}


gitstructure::gitstructure(){
    this->path = dd.currentDir();
}
gitstructure::~gitstructure(){

}