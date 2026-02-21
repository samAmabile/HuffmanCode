#include "huffman.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string> 
#include <iterator>
#include <iomanip>

using namespace std; 

string readFile(const string& filename){
    ifstream infile(filename, std::ios::binary);
    if (!infile) return ""; 
    
    return string({std::istreambuf_iterator<char>{infile}, std::istreambuf_iterator<char>{}});
}



int main(){

    //using ["Large Language Model Reasoning Failures" by Peiyang Song, Pengrui Han, Noah Goodman, 2026] for test
    
    string teststr = readFile("song_et_al.txt"); 
    cout<<"Original File: "<<endl;
    //cout<<teststr<<endl;

    
    Huffman codex(teststr); 

    vector<unsigned char> bitcode = codex.encode(teststr); 
    //cout<<"Encoded message: "<<endl;
    //for (unsigned char c: bitcode) cout<<c;

    double originalSize = (sizeof(char) * teststr.size());
    double compressedSize = (sizeof(unsigned char) * bitcode.size()); 
    double compressionRatio = compressedSize/originalSize; 

    string decoded = codex.decode(bitcode); 

    bool recovered = decoded == teststr ? true : false;

    cout<<"\n=========================RESULTS OF COMPRESSION================================="<<endl;

    if (recovered){
        cout<<"Recovered file succesfully"<<endl;
    }else{
        cout<<"Failed to properly decode compressed string"<<endl;
    }
    cout<<"Original string size: "<<fixed<<setprecision(2)<<originalSize<<endl;
    cout<<"Compressed string size: "<<compressedSize<<endl;
    cout<<"Ratio: "<<compressionRatio<<endl;
    cout<<"================================================================================"<<endl;
    cout<<endl; 
    cout<<endl; 
    //cout<<"Recovered message: "<<endl;
    //cout<<decoded<<endl;



    return 0;
}
