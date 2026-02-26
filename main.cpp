#include "huffman.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string> 
#include <iterator>
#include <iomanip>

using namespace std; 


//to read files in the fancy way. Prevents crashing on null characters, we hope. 
string readFile(const string& filename){
    ifstream infile(filename, std::ios::binary);
    if (!infile) return ""; 
    
    return string({std::istreambuf_iterator<char>{infile}, std::istreambuf_iterator<char>{}});
}



int main(){

    string filename;
    cout<<"Enter filename to compress: "<<endl;
    cin>>filename; 
    string teststr = readFile(filename); 
    
    

    
    Huffman codex(teststr); 

    vector<unsigned char> bitcode = codex.encode(teststr); 
    
    
    int originalLength = teststr.size();
    double originalSize = (sizeof(char) * teststr.size());
    int compressedLength = bitcode.size();
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
    cout<<"Original string bits: "<<fixed<<setprecision(2)<<originalSize*8<<endl;
    cout<<">>original character count: "<<originalLength<<endl;
    cout<<"Compressed string bits: "<<compressedSize*8<<endl;
    cout<<">>compressed character count: "<<compressedLength<<endl;
    cout<<"Ratio: "<<compressionRatio<<endl;
    cout<<">>savings of "<<(1-compressionRatio)*100<<"%"<<endl;
    cout<<"================================================================================"<<endl;
    cout<<endl; 
    cout<<endl; 



    return 0;
}
