#include "lib.h"
#include "gitstructure.h"
#include "Blob.h"
#include "config.h"
#include "myzlib.h"
#include "indexDB.h"
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
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        end - start
    );
    cout<<duration.count()<<" milliseconds"<<"\n";
    return 0;
}

