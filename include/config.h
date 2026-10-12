#pragma once
#include <string>
#include <map>
#include <vector>
#include <array>
using namespace std;
namespace config {
    bool init(const std::string &configPath);
    bool setmultiValues(vector<string[3]> CKV );
    bool setConfig(string cluster , string prameter , string value);
    string getValue(string cluster , string prameter);
    bool deletePrameter(string cluster , string prameter);
}
