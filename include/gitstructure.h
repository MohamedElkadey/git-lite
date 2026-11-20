#pragma once 
#include <bits/stdc++.h>
#include "asset.h"
using namespace std;
namespace fs = filesystem;


class gitstructure
{
private:
     string path;
    

    bool creategitDir();
    void createasset(const AssetInfo& asset);
    const AssetInfo& getInfo(Asset asset) const;
    string getDir() ;
    bool checkasset(const AssetInfo& asset);
    string findRepositoryRoot();
    
    
public:
    gitstructure(/* args */);
    ~gitstructure();
    void init();
    bool initConfig(Asset asset);
    

};

