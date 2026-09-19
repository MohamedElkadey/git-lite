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
    
    string objectD = "/run/media/elkadey/Engineering/test git/Test";
    string file2 = "/run/media/elkadey/Engineering/test git/file2.txt";
    string file3 = "/run/media/elkadey/Engineering/test git/try.txt";
    string file4 = "/run/media/elkadey/Engineering/test git/try2.txt";

    auto start = std::chrono::high_resolution_clock::now();
    Blob blb(objectD);
    cout<< blb.create(file2)<<'\n';
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        end - start
    );
    std::cout << "Function took: "
              << duration.count()
              << " microseconds\n";

              
    auto start2 = std::chrono::high_resolution_clock::now();
    cout<< blb.create(file4)<<'\n';
    auto end2 = std::chrono::high_resolution_clock::now();

    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(
        end2 - start2
    );
    std::cout << "Function took: "
              << duration2.count()
              << " microseconds\n";
    return 0;
}


