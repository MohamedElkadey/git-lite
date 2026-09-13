#pragma once
#include <bits/stdc++.h> 
using namespace std;

class myzlib
{
private:
    const size_t BUFFER_SIZE = 64*1024;
public:
    myzlib();
    void compressFile(ifstream& in, ofstream& out, int level);
    void decompressFile(ifstream& in, ofstream& out);
    ~myzlib();
};
