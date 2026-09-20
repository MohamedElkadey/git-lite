#include <bits/stdc++.h>


using namespace std;

/*
tree node [ file path with extention, hash , permissions ]
    each direcorty contain tree of files 

add file 

add . all 

savetree 
*/
vector<string> strFromPath(string path , vector<string>&res){
    string s="";
    for(int i=0;i<path.length();i++){
        if( path[i] == '/'){
            res.push_back(s);
            s ="";
        }
        s+=path[i];
    }
    if(!s.empty())
        res.push_back(s);
}

// bool addFile(string filePath , string hash){
//     try
//     {    
//         vector<string>res;
//         strFromPath(filePath,res);
//         DirectoryNode* current = &root;
//         for(size_t i = 0; i < res.size() - 1; i++){
//             string& dirName = res[i];
//             auto it = current->children.find(dirName);
//             if(it == current->children.end()){
//                 auto directory = make_unique<DirectoryNode>(dirName);
//                 DirectoryNode* directoryPtr = directory.get();
//                 current->children[dirName] = move(directory);
//                 current = directoryPtr;
//             }else{
//                 current =dynamic_cast<DirectoryNode*>(it->second.get());
//             }
//         }
//         string fileName = res.back();
//         current->children[fileName] = make_unique<FileNode>(fileName, hash);
//         return true;
        
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//         return false;
//     }
// }

bool createMasterDB(){

}
