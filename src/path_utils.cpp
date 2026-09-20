#include "path_utils.h"
#include "config.h"
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

static fs::path g_masterPath;

static void ensure_master(){
    if(g_masterPath.empty()){
        std::string m = config::getMasterPath();
        if(m.empty())
            g_masterPath = fs::current_path();
        else
            g_masterPath = fs::path(m);
    }
}

std::string path_utils::stripMasterPrefix(const std::string &absPath){
    ensure_master();
    try{
        fs::path p = fs::path(absPath);
        if(p == g_masterPath) return std::string(".");
        // if absPath starts with master path
        auto rel = fs::relative(p, g_masterPath);
        return rel.string();
    } catch(...) {
        return absPath;
    }
}

std::string path_utils::addMasterPrefix(const std::string &relPath){
    ensure_master();
    fs::path p = fs::path(relPath);
    if(p.is_absolute()) return p.string();
    fs::path joined = g_masterPath / p;
    return joined.lexically_normal().string();
}
