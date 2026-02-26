#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <vector>
#include <queue>

struct Node{
    char letter; 
    int freq; 

    Node* left;
    Node* right;

    Node(char l, int f): letter(l), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare{
    bool operator()(Node* l, Node* r){
        return l->freq > r->freq; 
    }
};

class Huffman{
private: 

    Node* _root;
    int _freq[256]{};
    std::string _codes[256]; 
    void _fdist(std::string);
    Node* _buildTree();
    void _makeCodes(Node*, std::string);
    void _clear(Node*);

public:
    
    Huffman();
    Huffman(const std::string&);
    ~Huffman();
    std::vector<unsigned char> encode(const std::string&);
    std::string decode(const std::vector<unsigned char>&);
    void setCode(const std::string&);

};

#endif
