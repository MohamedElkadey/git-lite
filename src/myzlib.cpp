#include <bits/stdc++.h> 
#include "myzlib.h"
#include "zlib.h"
using namespace std;

void myzlib::compressFile(ifstream& in, ofstream& out, int level) {
    /*
        ifstream in(file2, ios::binary);
        ofstream out(file3,  ios::binary | ios::trunc);
    */
    z_stream zs{};
    if (deflateInit(&zs, level) != Z_OK)
        throw runtime_error("deflateInit failed");

    vector<char> inBuf(BUFFER_SIZE);
    vector<char> outBuf(BUFFER_SIZE);

    int flush = Z_NO_FLUSH;
    do {
        in.read(inBuf.data(), inBuf.size());
        size_t n = (size_t)in.gcount();
        if (n == 0) flush = Z_FINISH;

        zs.next_in  = reinterpret_cast<Bytef*>(inBuf.data());
        zs.avail_in = (uInt)n;

        do {
            zs.next_out  = reinterpret_cast<Bytef*>(outBuf.data());
            zs.avail_out = (uInt)outBuf.size();

            int ret = deflate(&zs, flush);
            if (ret == Z_STREAM_ERROR)
                throw runtime_error("deflate failed");

            size_t produced = outBuf.size() - zs.avail_out;
            out.write(outBuf.data(), (streamsize)produced);
        } while (zs.avail_out == 0);
    } while (flush != Z_FINISH);

    deflateEnd(&zs);
}

void myzlib::decompressFile(ifstream& in, ofstream& out) {
    z_stream zs{};
    if (inflateInit(&zs) != Z_OK)
        throw runtime_error("inflateInit failed");

    vector<char> inBuf(BUFFER_SIZE);
    vector<char> outBuf(BUFFER_SIZE);

    int ret = Z_OK;
    do {
        if (zs.avail_in == 0) {                 // need more input
            in.read(inBuf.data(), inBuf.size());
            size_t n = (size_t)in.gcount();
            if (n == 0) break;                  // truncated stream
            zs.next_in  = reinterpret_cast<Bytef*>(inBuf.data());
            zs.avail_in = (uInt)n;
        }

        zs.next_out  = reinterpret_cast<Bytef*>(outBuf.data());
        zs.avail_out = (uInt)outBuf.size();

        ret = inflate(&zs, Z_NO_FLUSH);
        if (ret != Z_OK && ret != Z_STREAM_END)
            throw runtime_error("inflate failed");

        size_t produced = outBuf.size() - zs.avail_out;
        out.write(outBuf.data(), (streamsize)produced);
    } while (ret != Z_STREAM_END);

    inflateEnd(&zs);
}
myzlib::myzlib(){}
myzlib::~myzlib(){}