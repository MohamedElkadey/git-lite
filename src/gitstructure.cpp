#include "gitstructure.h"
#include "config.h"
#include "path_utils.h"
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
            createasset(info.asset);
            if(info.childrenCount){
                for (size_t i = 0; i < info.childrenCount; ++i){
                    const auto& child = info.children[i];
                    createasset(child.asset);
                }
            }
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
        if(!config::init(path)){
            cout << "Failed to init config: " << path << "\n";
            return false;
        }
        if(config::getMasterPath().empty()){
            
            if(!config::setMasterPath(this->path)){
                cout << "Failed to set master path in config\n";
                return false;
            }
        }
    }

    if(info.type == AssetType::File){
        file f;
        return f.create(path);
    }

    return false;
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
    }else if(info.type == AssetType::File){
        return !dd.fileExist(path) ;
    }

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