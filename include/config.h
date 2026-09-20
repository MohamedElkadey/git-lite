#pragma once
#include <string>
#include <vector>
using namespace std;
namespace config {
    bool init(const std::string &configPath);
    string getMasterPath();
    bool setMasterPath(const std::string &masterPath);
    bool setmultiValues(vector<string[3]> CKV );
    bool setConfig(string cluster , string prameter , string value);
}
