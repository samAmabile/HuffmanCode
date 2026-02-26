#include "compressor.h"

#include <iostream>
#include <filesystem>


namespace fs = std::filesystem;
using namespace std; 

void printFileStats(const std::string& filename){
    cout<<"==========================================================="<<endl;
    cout<<filename<<": "<<endl;
    auto size = fs::file_size(filename);
    auto bytes = size*8;
    cout<<"Size: "<<endl;
    cout<<"bits: "<<size<<endl;
    cout<<"bytes: "<<bytes<<endl;
    cout<<"==========================================================="<<endl;
}


int main(int argc, char* argv[]){

    string instr = "";
    string outstr = "";

    if (argc <= 1){
        instr = "song_et_al.txt";
        outstr = "song_bitstr.txt";
    }else if (argc == 3){
        instr = argv[1]; 
        outstr = argv[2];
    }else {
        cerr<<"Too many filenames, run program with [executable, file to compress, filename to save compressed file]"<<endl;
        return 0; 
    }

    Compressor compressor; 

    if (compressor.compressTo(instr, outstr)) {
        cout<<"File compressed to: "<<outstr<<endl;
    }else  {
        cout<<"compression failed"<<endl;
        return 1; 
    }

    fs::path p(instr);
    string base = p.stem().string();
    string recovered = base+"_recovered.txt";


    if (compressor.extractTo(outstr, recovered)) {
        cout<<"File recovered to song_recovered.txt"<<endl;
    }else {
        cout<<"file extraction failed"<<endl;
        return 1; 
    }
    
    printFileStats(instr);
    printFileStats(outstr);


    return 0; 
}

