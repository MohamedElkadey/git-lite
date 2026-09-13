#pragma once
#include <bits/stdc++.h>

using namespace std;
namespace fs = filesystem;
/*
[cluster]
    "key":"type"="value"
*/
class INIFile
{
public:
    struct Field{
        uint32_t start;
        uint32_t length;
    };
    
    struct Key
    {
        Field Posetion;
        string name;
    };
    
    struct Entry{
        Key key;
        Field type;
        Field value;
    };

    struct Read{
        Field cluster ;
        string name;
        vector<Entry> children;
    };

private:
    fs::path filePath;
    const size_t BUFFER_SIZE = 64*1024;
    struct Edit {
        uint32_t start; // included
        uint32_t end;   // excluded
        string replacement;
    };
    vector<Edit>edits ;


    bool createFile(fs::path);
    string ClusterFrom(string , string );
    bool checkClusterInLine(string , string );
    bool createPath(fs::path );

public:
    INIFile();
    bool init(string);
    Read getCluster(string);
    string readByChunck();
    ~INIFile();
    Key readChunk(ifstream&);
};

INIFile::INIFile(){}

bool INIFile::init(string filePath){
    fs::path fp = fs::path(filePath); 
    if(!fs::exists(fp)){
        if(!createFile(fp)){
            cout<<"faild to create file\n";
            return false;
        }
    }
    this->filePath = fp;
    return true;
}

bool INIFile::createFile(fs::path path){
    if(fs::exists(path))
        return true;

    if(path.parent_path().empty()){
        if(!createPath(path.parent_path()))
            return false;
    }
    fstream file(path);

    return file.is_open();
}

bool INIFile::createPath(fs::path path){
    if(fs::exists(path))
        return true;
    
    if(path.parent_path().empty()){
        if(!createPath(path.parent_path())){
            return false;
        }
    }
    return fs::create_directory(path);
}

INIFile::~INIFile(){}

// INIFile::Read INIFile::getCluster(string Cluster){
//     ifstream file;
//     file.open(filePath.string(),ios::binary);
//     if (!file.is_open())
//         return {};

//     string result;
//     uint32_t st;
//     uint32_t end;
//     while (file)
//     {
//         Read chunk = readChunk(file);
//         if(chunk.data.empty())
//             break;
//         result += ClusterFrom(chunk.data.data() , Cluster);
//     }
//     return result;
// }

string INIFile::ClusterFrom(string content, string Cluster){
    string line,result ="";
    uint32_t st,ed;
    bool readed = 0,aim =0;
    istringstream stream(content);
    while (getline(stream , line))
    {
        if(!line.empty() && line[0] == '['){
            if(aim){
                readed = true;
                break;
            }
            aim = checkClusterInLine(Cluster,line);
            continue;
        }
        if(aim && !readed){
            result += line + '\n';
        }
        if(readed)
            break;
    }
    return result;
}

bool INIFile::checkClusterInLine(string Cluster , string line){
    string cl= "";
    for(unsigned int i = 1 ;i<line.length() ; i++){
        if(line[i] != ']'){
            cl += line[i];
        }
    }
    return cl == Cluster;
}

string INIFile::readByChunck(){
    ifstream file;
    file.open(filePath.string(),ios::binary);
    if (!file.is_open())
        return {};

    string result;
    while(file){
        Key reads = readChunk(file);
        if(reads.Posetion.length == 0)
            break;
        result += reads.name;
    }

    return result;
}

INIFile::Key INIFile::readChunk(ifstream& file){
    vector<char> buffer(BUFFER_SIZE);

    uint32_t start = static_cast<uint32_t>(file.tellg());

    file.read(buffer.data(), BUFFER_SIZE);

    uint32_t bytesRead = static_cast<uint32_t>(file.gcount());

    return Key{ Field{start, bytesRead}, string(buffer.data(), bytesRead)};
}


/*
read file by chunk with return start and end byte
read Cluseter return string and start and end bytes
edit(cluster , key )-> (start , end)for key -> save edit in vector 
    "key":"type"="val"
sort edit with start -> function to overlap to make edit vector

apply edit -> read the file and write the new things in temp file

*/
