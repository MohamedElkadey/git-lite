#include "gitstructure.h"
#include "config.h"
#include "lib.h"
#include "asset.h"

gitstructure::gitstructure(){
    string path = findRepositoryRoot();
    if(!path.empty()){
        this->path = path;
    }else{
        auto root = fs::current_path();
        this->path = root.string();
    }
    setRootPath(this->path);

}
void gitstructure::init(){
    if (!dd.dirExist(getDir())) {
        dd.createDir(getDir());
    }
    for( const auto& info : assetsMap){
        if (!checkasset(info.second)) {
            createasset(info.second);
            if(info.second.childrenCount){
                for (size_t i = 0; i < info.second.childrenCount; ++i){
                    auto child = info.second.children[i];
                    createasset(child);
                }
            }
        }
    }
}
string gitstructure::findRepositoryRoot() {
    fs::path current = fs::current_path();

    while (true) {
        if (fs::exists(current / gtDir)) {
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
    return dd.createDirPath(gtDir );
}

void gitstructure::createasset(const AssetInfo& asset)
{
    if(asset.ops && asset.ops->create){
        asset.ops->create(asset);
    }
}


bool gitstructure::checkasset(const AssetInfo& asset){
    if(asset.ops && asset.ops->validate){
        return asset.ops->validate(asset);
    }
    return true;
}

string gitstructure::getDir(){
     return this->path +'/'+ gtDir ;
}

gitstructure::~gitstructure(){

}