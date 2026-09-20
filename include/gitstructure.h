#pragma once 
#include <bits/stdc++.h>
using namespace std;
namespace fs = filesystem;

class gitstructure
{
private:
     string path;
    const string gtDir = ".gt";
    enum class Asset : uint8_t {
        Blob, 
        Tree, 
        Index, 
        Ignore,
        Config
    };
    enum class AssetType : uint8_t{
        Directory,
        File
    };
    struct AssetInfo{
        Asset asset;
        const char* name ;
        AssetType type;
        const AssetInfo* children;
        size_t childrenCount;
    };
    // static constexpr AssetInfo blobAssets[] = {
    //     {Asset::Blob, "something", AssetType::File, nullptr, 0},
    //     {Asset::Blob, "else", AssetType::File, nullptr, 0}
    // };
    
    static constexpr array<AssetInfo , 5> assets= {{
        {Asset::Blob , "object", AssetType::Directory,nullptr ,0},
        {Asset::Tree , "DB", AssetType::Directory,nullptr,0},
        {Asset::Index , "index.db", AssetType::File,nullptr, 0},
        {Asset::Ignore , "ignore.txt", AssetType::File ,nullptr,0},
        {Asset::Config , "Config.ini", AssetType::File ,nullptr,0}
    }};


    map<string,int> checkstrucute();
    bool creategitDir();
    bool createasset(Asset asset);
    const AssetInfo& getInfo(Asset asset) const;
    bool havegitDir();
    string getPath(Asset asset) const;
    string getDir() const;
    int checkasset(Asset asset);
    int setbit(int , int );
    string findRepositoryRoot();
    
public:
    gitstructure(/* args */);
    ~gitstructure();
    void init();
    

};

