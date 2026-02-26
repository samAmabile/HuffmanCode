#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "huffman.h"
#include <fstream>
#include <iterator>
#include <vector>


class Compressor{
private:
    Huffman _codex; 

public:
    Compressor();
    std::vector<unsigned char> compress(const std::string&);
    std::string extract(std::vector<unsigned char>&);
    bool save(std::vector<unsigned char>&, const std::string&);
    std::vector<unsigned char> loadBitstr(const std::string&);
    std::string loadFile(const std::string&);
    std::vector<unsigned char> compressFile(const std::string&);
    std::string extractFile(const std::string&); 
    bool extractTo(const std::string&, const std::string&);
    bool compressTo(const std::string&, const std::string&);
};

#endif


