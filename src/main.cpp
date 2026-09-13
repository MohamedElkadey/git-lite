#include <bits/stdc++.h>
#include "gitstructure.h"
#include "Blob.h"
#include "file.h"
#include "dir.h"
#include "myzlib.h"
#include "INIFile.h"

using namespace std;


int main(){
    cout<<"Hello\n";
    // gitstructure gt ;
    // gt.init();
    
    string file1 = "/run/media/elkadey/Engineering/test git/file.ini";
    string file2 = "/run/media/elkadey/Engineering/test git/file2.txt";
    string file3 = "/run/media/elkadey/Engineering/test git/try.txt";
    string file4 = "/run/media/elkadey/Engineering/test git/try2.txt";

    ifstream in(file2, ios::binary);
    ofstream out(file3,  ios::binary | ios::trunc);
    auto start2 = std::chrono::high_resolution_clock::now();
    file fl;
    myzlib zl;
    cout<<fl.hashFileContent(file2)<<'\n';
    zl.compressFile(in,out,8);
    in.close();
    out.close();
    ifstream in2(file3, ios::binary);
    ofstream out2(file4,  ios::binary | ios::trunc);
    zl.decompressFile(in2,out2);
    in2.close();
    out2.close();
    cout<<fl.hashFileContent(file4)<<'\n';
    cout<<fl.fileSize(file2)<<'\n';
    cout<<fl.fileSize(file4)<<'\n';

    auto end2 = std::chrono::high_resolution_clock::now();

    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(
        end2 - start2
    );
    std::cout << "Function took: "
              << duration2.count()
              << " microseconds\n";

    return 0;
}


