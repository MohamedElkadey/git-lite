#pragma once
#include <string>

namespace path_utils {
    std::string stripMasterPrefix(const std::string &absPath);
    std::string addMasterPrefix(const std::string &relPath);
    std::string getMaster();
    void setMaster(std::string path);
}
