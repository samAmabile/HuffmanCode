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

string changeExt(const string& filename, const string& extension){
        fs::path p(filename);
        string base = p.stem().string();
        return base+extension;
}

string pzip = ".pzip";
string txt = ".txt";

string helpmenu = R"(
to compress file: protozip <filename>
to compress file and save as: protozip <filename> <save as>
to extract file: protozip --extract <filename>
to extract file and save as: protozip --extract <filename> <save as>
)";


int main(int argc, char* argv[]){

    string instr = "";
    string outstr = "";
    string extract_flag = "--extract";
    bool extract = false;

    if (argc <= 1){
        cerr<<"!Invalid Command!"<<endl;
        cout<<helpmenu<<endl;
        return 1;
    }
    if (argc == 2){
        instr = argv[1];
        outstr = changeExt(instr, pzip);
    }else if (argc == 3){
        if (argv[1] == extract_flag){
            instr = argv[2];
            outstr = changeExt(instr, txt);
            extract = true;
        }else{
            instr = argv[1];
            outstr = argv[2];
        }
    }else if (argc == 4){
        if (argv[1] == extract_flag){
            instr = argv[2];
            outstr = argv[3];
            extract = true;
        }else {
            cerr<<"!Too many/Invalid arguments!"<<endl;
            cout<<helpmenu<<endl;
            return 1;
        }
    }else {
        cerr<<"!Too many arguments!"<<endl;
        cout<<helpmenu<<endl;
    }


    Compressor compressor; 

    if (extract){

        if (compressor.extractTo(instr, outstr)) {
            cout<<"File recovered to: "<<outstr<<endl;
            printFileStats(outstr);
        }else {
            cerr<<"file extraction failed"<<endl;
            return 1; 
        }

    }else{

        if (compressor.compressTo(instr, outstr)) {
            cout<<"File compressed to: "<<outstr<<endl;
            printFileStats(outstr);
        }else  {
            cerr<<"compression failed"<<endl;
            return 1; 
        }

    }

    


    return 0; 
}

//OLD CODE:

    /*if (argc <= 1){
        instr = "song_et_al.txt";
        outstr = "song_bitstr.txt";
    }else if (argc == 3){
        instr = argv[1]; 
        outstr = argv[2];
    }else {
        cerr<<"Too many filenames, run program with [executable] [file to compress] [filename to save compressed file]"<<endl;
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
        cout<<"File recovered to: "<<recovered<<endl;
    }else {
        cout<<"file extraction failed"<<endl;
        return 1; 
    }*/

