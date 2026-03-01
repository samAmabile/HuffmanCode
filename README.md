# ProtoZip File Compression Tool
Command-line file compression tool using Huffman Code. 

Compress, Save, and Extract files quicky and easily from the terminal. 

Saves files with `.pzip` extension for easy identification

***clone repo and run `make` to compile, then `./protozip <filename>` to compress a file. run with `--extract` flag to recover .pzip files 

## Rundown
ProtoZip uses Huffman Code, which is a prefix-free encoding scheme that is used by many string compression programs including ZST.

Simple CLI makes ProtoZip function similar to other command line tools for file manipulation and analysis. 

Huffman code use a "simple" string compression/encoding scheme that builds a binary tree mapping characters to unique binary encodings by frequency. 
Encoding is for compression only, not at all meant to be secure. I wanted to learn it to use in corpus building and working with huge amounts of text, to save space. 
Though there is probably a much simpler solution for that, and many versions of Huffman that are better than mine, but here we are. Thanks for looking. 

### Huffman Class
A data structure implementation of the Huffman Code tree. Uses priority queue and integer array to sort characters by frequency and build the encoding tree. 
The encoding scheme is saved as a header on the bit string so the decode function knows how to decode, because each file will have a unique binary tree.
***use main.cpp to test this on a file and see savings from compression

### Compressor Class
A simple implementation of file compression using the Huffman Code data structure/algorithm. Allows file loading, encoding, saving, and decoding from command line. 
***use compmain.cpp to compress files, save the compressed version, and decompress/extract files encoded with Huffman Code 

#### Files
* ProtoZip file compression tool:
```
Makefile -- compiles huffman, compressor, and compmain into executable `./protozip`
```
* Huffman Code data structure:
```
huffman.h -- header for Huffman class
huffman.cpp -- function definitions for Huffman class
main.cpp -- a main function for testing the compression, no file saving
```
* Compressor Class:
```
compressor.h -- header for Compressor class
compressor.cpp -- function definitions for Compressor
compmain.cpp -- main CLI logic for ProtoZip, takes filenames in and uses compressor class to encode/decode
```
* Test files:
```
song_et_al.txt -- "_Large Language Model Reasoning Failures by Peiyang Song, Pengrui Han, Noah Goodman; 2026; Cornell_", used for the tests
song_bitstr.txt -- example of compressed file
song_et_al_recovered.txt -- example of recovered file
```
#### Requirements: 
* C++ 17 or above
* thats it i think, a compiler

### To Run:
* #### ProtoZip: 
to compress a single file:
```bash
make
./protozip <filename>
```
to compress a file and save as: 
```bash
make
./protozip <filename> <save as>
```
**Output: 
```console
File compressed to: song_bitstr.txt
===========================================================
song_bitstr.txt: 
Size: 
bits: 146526
bytes: 1172208
===========================================================
```
to extract a single `.pzip` file: 
```bash
make
./protozip --extract <filename>
```
to extract and save as: 
```bash
make
./protozip --extract <filename> <save as>
```
**Output:
```console
File recovered to song_recovered.txt
===========================================================
song_recovered.txt: 
Size: 
bits: 229526
bytes: 1836208
===========================================================
```

### To test compression results

* #### main.cpp (test Huffman Code on a file)
```bash
g++ -O3 huffman.cpp main.cpp -o huffman
./huffman
```
* main.cpp outputs stats about compression to console

**Output:** 

```console
Enter filename to compress: 
song_et_al.txt

=========================RESULTS OF COMPRESSION=================================
Recovered file succesfully
Original string bits: 1836208.00
>>original character count: 229526
Compressed string bits: 1172208.00
>>compressed character count: 146526
Ratio: 0.64
>>savings of 36.16%
================================================================================
```




