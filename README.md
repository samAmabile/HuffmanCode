# HuffmanCode
Just like it sounds, an implementation of HuffmanCode string compression in C++, written mostly by looking things up.

## Rundown
Huffman code, which if you are looking at this you probably know better than I, is a "simple" string compression/encoding scheme that uses a binary tree to map chars by frequency. 
I think it is primarily for compression, not at all meant to be secure. I wanted to learn it to use in corpus building and working with huge amounts of text, to save space. 
Though there is probably a much simpler solution for that, and many versions of Huffman that are better than mine, but here we are. Thanks for looking. 

* **Note** I used _Large Language Model Reasoning Failures by Peiyang Song, Pengrui Han, Noah Goodman; 2026; Cornell_ for the test

### Requirements: 
* C++ 17 or above
* thats it i think, a compiler

### To Run:
* I used 'g++' compiler, and '-O3' for efficiency, you do you. 
```bash
g++ -O3 huffman.cpp main.cpp
./a.out
```
### Output:
* program currently just outputs stats:

```
=========================RESULTS OF COMPRESSION=================================
Recovered file succesfully
Original string size: 229526.00
Compressed string size: 146526.00
Ratio: 0.64
================================================================================
```

You can uncomment out the print statements for the test file if you want to see the encoding, if thats something you are into


