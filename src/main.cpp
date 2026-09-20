#include <bits/stdc++.h>
#include "gitstructure.h"
#include "Blob.h"
#include "file.h"
#include "dir.h"
#include "myzlib.h"
#include "inicpp.h"

using namespace std;


int main(){
    
    
    string base = "/run/media/elkadey/Engineering/test git/";
    string file2 = "/run/media/elkadey/Engineering/test git/file.ini";
    string file3 = "/run/media/elkadey/Engineering/test git/try.txt";
    string file4 = "/run/media/elkadey/Engineering/test git/try2.txt";

    auto start = std::chrono::high_resolution_clock::now();
    
cout<<"Hello\n";
    gitstructure gt ;
    gt.init();
    

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        end - start
    );
    cout<<duration.count()<<"\n";
    return 0;
}


