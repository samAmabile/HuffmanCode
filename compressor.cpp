#include "compressor.h"
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <iostream>


//==============================helper functions:===============================//

std::string readFile(const std::string& filename){
    
    std::ifstream infile(filename, std::ios::binary | std::ios::ate);
    if (!infile) return "";

    std::streamsize size = infile.tellg();
    if (size <= 0) return "";

    infile.seekg(0, std::ios::beg);

    std::string buffer; 
    buffer.reserve(size);
    buffer.assign((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());

    return buffer;
}

void writeFile(const std::string& content, const std::string& filename){

    
    std::ofstream outfile(filename, std::ios::out | std::ios::binary);
    outfile.write(content.data(), content.size()); 
    

}
 
//=============================class member functions:===========================//
Compressor::Compressor(){}

Compressor::Compressor(const std::string& filename){
    std::string content = readFile(filename); 
    _codex.setCode(content);
    _codeSet = true;
}

std::vector<unsigned char> Compressor::compress(const std::string& text){
    if (!_codeSet){
        _codex.setCode(text);
        _codeSet = true;
    }
    return _codex.encode(text);
}

std::string Compressor::extract(std::vector<unsigned char>& bitstr){
    return _codex.decode(bitstr);
}

std::string Compressor::loadFile(const std::string& filename){
    return readFile(filename);
}

std::vector<unsigned char> Compressor::compressFile(const std::string& filename){
    std::string content = loadFile(filename); 
    return compress(content);
}
bool Compressor::compressTo(const std::string& infile, const std::string& outfile){
    std::vector<unsigned char> bitstr = compressFile(infile);
    if (save(bitstr, outfile)){
        return true;
    }else{
        return false;
    }
    return false;
}

bool Compressor::save(std::vector<unsigned char>& bitstr, const std::string& filename){
    if (bitstr.empty()) return false;

    std::ofstream outfile(filename, std::ios::binary);

    if (outfile.is_open()){
        outfile.write(reinterpret_cast<const char*>(bitstr.data()), bitstr.size());
        return true;
    }else{
        std::cout<<"Writing bitcode file failed"<<std::endl;
        return false;
    }
    return false;

}

std::vector<unsigned char> Compressor::loadBitstr(const std::string& filename){
    std::string bitstr = readFile(filename);
    return std::vector<unsigned char>(bitstr.begin(), bitstr.end());
}

std::string Compressor::extractFile(const std::string& filename){
    std::vector<unsigned char> bitstr = loadBitstr(filename);
    return extract(bitstr);
}

bool Compressor::extractTo(const std::string& infile, const std::string& outfile){
    std::string content = extractFile(infile); 
    writeFile(content, outfile);
    return true;
}



