#include "huffman.h"

#include <vector>
#include <string>
#include <cstring>
#include <iostream>


Huffman::Huffman(){};
Huffman::Huffman(const std::string& text){
    setCode(text);
}
Huffman::Huffman(const Huffman& h){
    std::memcpy(_freq, h._freq, sizeof(_freq));
    for (int i=0; i<256; ++i){
        _codes[i] = h._codes[i];
    }
    _root = _copy(h._root);
}
Huffman& Huffman::operator=(const Huffman& h){
    if (this == &h) return *this;

    _clear(_root);
    for (int i=0; i<256; ++i){
        _freq[i] = h._freq[i];
        _codes[i] = h._codes[i];
    }

    _root = _copy(h._root);

    return *this;
}
Huffman::~Huffman(){
    _clear(_root);
}
void Huffman::setCode(const std::string& text){
    _fdist(text);
    _root = _buildTree();
    _makeCodes(_root, "");
}
void Huffman::_fdist(std::string msg){
    for (char c: msg){
        _freq[static_cast<unsigned char>(c)]++;
    }
}
Node* Huffman::_buildTree(){
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for (int i=0; i<256; ++i){
        if (_freq[i] != 0){
            Node* newNode = new Node(static_cast<char>(i), _freq[i]);
            pq.push(newNode);
        }
    }
    
    while(pq.size() > 1){
        Node* a = pq.top(); pq.pop(); 
        Node* b = pq.top(); pq.pop(); 
        int sum_ = a->freq + b->freq; 
        Node* parent = new Node('\0', sum_); 
        parent->left = a; 
        parent->right = b;
        pq.push(parent);
    }

    if (!pq.empty()){
        Node* top = pq.top();
        pq.pop(); 
        return top;
    }
    return nullptr;
}
void Huffman::_makeCodes(Node* cur, std::string code){
    if (!cur) return;
    if (!cur->right && !cur->left){
        _codes[static_cast<unsigned char>(cur->letter)] = code;
        return;
    }
    _makeCodes(cur->left, code+"0");
    _makeCodes(cur->right, code+"1");
}
Node* Huffman::_copy(Node* root){
    if (!root) return nullptr;
    Node* newRoot = new Node(root->letter, root->freq);
    newRoot->left = _copy(root->left);
    newRoot->right = _copy(root->right);
    return newRoot;
}
void Huffman::_clear(Node* node){
    if (!node) return;
    _clear(node->left);
    _clear(node->right);
    delete node;
}

//===============================PUBLIC FUNCTIONS:========================================//

std::vector<unsigned char> Huffman::encode(const std::string& msg){

    std::vector<unsigned char> bytes; 
    bytes.reserve(msg.size()*8);

    size_t msg_size = msg.size(); 
    unsigned char* sizeBytes = reinterpret_cast<unsigned char*>(&msg_size);

    for (int i=0; i<sizeof(size_t); i++){
        bytes.emplace_back(sizeBytes[i]);
    }

    for (int i=0; i<256; i++){
        int f = _freq[i];
        unsigned char* fbytes = reinterpret_cast<unsigned char*>(&f); 
        for (int j=0; j<sizeof(int); j++){
            bytes.emplace_back(fbytes[j]);
        }
    }


    unsigned char local = 0;
    int bitcount = 0;
    for (char c: msg){
        std::string bitstr = _codes[(unsigned char)c];
        for (char b: bitstr){ 
            local = (local << 1) | b - '0';
            if (++bitcount == 8){
                bytes.emplace_back(local);
                local = 0;
                bitcount = 0; 
            }
        }
    }
    if (bitcount > 0){
        local <<= (8-bitcount); 
        bytes.emplace_back(local);
    }
    return bytes;
}

std::string Huffman::decode(const std::vector<unsigned char>& huffcode){

    //read size and encoding from top of charvector:
    size_t msgsize = 0; 
    std::memcpy(&msgsize, &huffcode[0], sizeof(size_t));
    //msgsize = *reinterpret_cast<const size_t*>(&huffcode[0]); 
    int offset = sizeof(size_t);

    for (int i=0; i<256; i++){
        _freq[i] = 0; 
    }

    for (int i=0; i<256; i++){
        std::memcpy(&_freq[i], &huffcode[offset], sizeof(int));
        offset += sizeof(int); 
    }

    _clear(_root);

    _root = _buildTree();
    if (!_root) return "";

    std::string result = "";
    Node* cur = _root;
    size_t decoded_sofar = 0; 

    for (auto i{offset}; i<huffcode.size(); ++i){
        unsigned char byte = huffcode[i];

        //bitwalk:
        for (int bit=7; bit>=0; --bit){
            bool isOne = (byte >> bit) & 1;

            if (isOne){
                cur = cur->right; 
            }else{
                cur = cur->left;
            }
            if (!cur) std::cerr<<"**Huffman reached Null Node, segfault prevented, decode terminated**"<<std::endl;

            if (cur && !cur->left && !cur->right){
                result += cur->letter; 
                decoded_sofar++;
                cur = _root;
            }
            if (decoded_sofar == msgsize) return result; 
        }

    }
    return result; 
}




            
        
         
    













