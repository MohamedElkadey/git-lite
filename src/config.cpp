#include "config.h"
#include "inicpp.h"
#include <bits/stdc++.h>
#include "path_utils.h"
#include "file.h"

using namespace std;
namespace fs = filesystem;

static fs::path g_configPath;
static string g_masterPath ;
static ini::IniFile configFile;

bool config::init(const string &configPath){
    g_configPath = fs::path(configPath);
    file fl;
    return fl.checkExistOrCreate(configPath);
}

string config::getMasterPath(){
    if(!g_masterPath.empty())
        return g_masterPath;
    if(!g_configPath.empty()){
        configFile.load(g_configPath);
        return getValue( "settings","master");
    }
    return "";
}   

bool config::setMasterPath(const string &masterPath){
    g_masterPath = masterPath;
    return setConfig("settings" , "master" ,g_masterPath );
}
string config::getValue(string cluster , string prameter){
    configFile.load(g_configPath);
        return configFile[cluster][prameter].as<string>();
}

bool config::setConfig(string cluster , string prameter , string value){
    try
    {
        configFile.load(g_configPath.string());
        configFile[cluster][prameter] =value;
        configFile.save(g_configPath.string());
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

bool config::setmultiValues(vector<string[3]> CKV ){
    try
    {
        configFile.load(g_configPath.string());
        for(auto CV : CKV){
            configFile[CV[0]][CV[1]] =CV[2];
        }
        configFile.save(g_configPath.string());
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return false;   
}
bool config::deletePrameter(string cluster , string prameter){
    try
    {
        configFile.load(g_configPath.string());
        configFile[cluster].erase(prameter);
        configFile.save(g_configPath.string());
        return true;    
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    
    
}