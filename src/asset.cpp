#include "asset.h"
#include "lib.h"
#include "indexDB.h"
#include <map>
std::string rootDir;

void setRootPath(string& path){
    rootDir = path;
    string path_utils_path =path_utils::getMaster();
    if(path_utils_path.empty()){
        path_utils::setMaster(rootDir);
    }else{
        if(path_utils_path != rootDir){
            rootDir = path_utils_path;
        }
    }
}


const AssetInfo& getInfo(Asset asset) {
    AssetInfo info = assetsMap.at(asset);
    return info;
}

string getPath(AssetInfo asset) {
    string name = asset.name ? asset.name : "";
    string ext = asset.dotExtension?asset.dotExtension:"";
    return path_utils::addMasterPrefix(gtDir+'/'+ name + ext);
}


bool validateConfig(const AssetInfo& Config){
    return fl.checkFileExist(getPath(Config));
}

void createConfig(const AssetInfo& config){
    string path = getPath(config);
    if(!config::init(path)){
        cout << "Failed to init config: " << path << "\n";
        return ;
    }
    return ;
}

bool validateObject(const AssetInfo& asset){
    return dd.dirExist(getPath(asset));
}

void createObject(const AssetInfo& asset){
    dd.createDir(getPath(asset));
}

bool validateDB(const AssetInfo& asset){
    return dd.dirExist(getPath(asset));
}

void createDB(const AssetInfo& asset){
    dd.createDir(getPath(asset));
}

bool validateIndex(const AssetInfo& asset){
    return fl.checkFileExist(getPath(asset));
}

void createIndex(const AssetInfo& asset){
    indexDB db;
    db.setindexDB();
}
void creareIgnore(const AssetInfo& asset){
    fl.create(getPath(asset));    
}
bool validateIgnore(const AssetInfo& asset){
    return fl.checkFileExist(getPath(asset));
}


const AssetOps ConfigOps {
    validateConfig,
    createConfig
};

const AssetOps objectOps {
    validateObject,
    createObject
};

const AssetOps DBOps {
    validateDB,
    createDB
};

const AssetOps IndexOps{
    validateIndex,
    createIndex
};
const AssetOps IgnoreOps{
    validateIgnore,
    creareIgnore
};

// ToDo 
/*
crate tree DB AssetOps
crate ignore AssetOps
*/

const std::map<Asset,AssetInfo> assetsMap = {{
    {Asset::Config, {"Config", ".ini", AssetType::File, nullptr, 0,&ConfigOps}},
    {Asset::Blob,   {"object", nullptr, AssetType::Directory, nullptr, 0,&objectOps}},
    {Asset::TreeDir,{"DB",     nullptr, AssetType::Directory, nullptr, 0,&DBOps}},
    {Asset::Index,  {"index",  ".db", AssetType::File, nullptr, 0,&IndexOps} },
    {Asset::Tree,   {"tree",   ".db", AssetType::File, nullptr, 0,nullptr}},
    {Asset::Ignore, {"ignore", ".txt", AssetType::File, nullptr, 0,&IgnoreOps}}
}};