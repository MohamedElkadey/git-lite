#include "dir.h"
#include <bits/stdc++.h>
using namespace std;
namespace fs = filesystem;


bool dir::dirExist(string dPath){
    try
    {
        fs::path dirpath = fs::path(dPath);

        if(!fs::exists(dirpath)){
            return false;
        }
        if(!fs::is_directory(dirpath)){
            return false;
        }
    }
    catch(const std::exception& e)
    {
        cout << e.what() << '\n';
        return false;
    }
    return true;
}

bool dir::fileExist(string fpath){
    fs::path path = fs::path(fpath);
    if(!fs::exists(path))
        return false;

    if(!fs::is_regular_file(path)){
        return false;
    }
    return true;
}

string dir::currentDir(){
    return fs::current_path().string();
}

bool dir::createDir(string path ){
    fs::path  directory =  path ;
    if(this->dirExist(directory.string())){
        cout<<path + " is exits";
        return true;
    }
    try
    {
        if(fs::create_directory(directory)){
            cout<<"directory " << directory <<"is created \n";
            return true;
        }else{
            cout<<"can\'t create directory "<<directory<<"\n";
            return false;
        }
    }
    catch(const std::exception& e)
    {
        cout << e.what() << '\n';
        return false;
    }
}

bool dir::createDirPathR(fs::path& path){
    if(dirExist(path.string()))
        return true;
    fs::path parent_path = path.parent_path();

    if(!parent_path.empty() && !dirExist(parent_path.string())){
        if (!createDirPathR(parent_path))
            return false;
    }

    return createDir(path.string());
}
bool dir::createDirPath(string path){
    fs::path dpath = fs::path(path);
    return createDirPathR(dpath);
}



dir::dir(){}
dir::~dir(){}