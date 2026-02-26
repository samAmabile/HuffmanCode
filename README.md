# HuffmanCode Compressor
Just like it sounds, an implementation of HuffmanCode string compression in C++, written mostly by looking things up, and tracking down segmentation faults for many hours. 

## Rundown
Huffman code, which if you are looking at this you probably know better than I, is a "simple" string compression/encoding scheme that uses a binary tree to map chars by frequency. 
I think it is primarily for compression, not at all meant to be secure. I wanted to learn it to use in corpus building and working with huge amounts of text, to save space. 
Though there is probably a much simpler solution for that, and many versions of Huffman that are better than mine, but here we are. Thanks for looking. 

### Huffman Class
A data structure implementation of the Huffman Code tree. Uses priority queue and integer array to sort characters by frequency and build the encoding tree. 
The encoding scheme is saved as a header on the bit string so the decode function knows how to decode, because each file will have a unique binary tree.
***use main.cpp to test this on a file and see savings from compression***

### Compressor Class
A simple implementation of file compression using the Huffman Code data structure/algorithm. Allows file loading, encoding, saving, and decoding from command line. 
***use compmain.cpp to compress files, save the compressed version, and decompress/extract files encoded with Huffman Code***

#### Files
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
compmain.cpp -- main function to test file compressing, saves and extracts files
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

#### To Run:
##### main.cpp (test Huffman Code on a file)
```bash
g++ -O3 huffman.cpp main.cpp
./huffmanstats.o
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
##### compmain.cpp (compress, save, and extract files using Compressor class)
Program takes filenames as arguments in the order *executable  filename  save_as*
```bash
g++ -O3 huffman.cpp compressor.cpp compmain.cpp 
./compressor.o file_to_compress.txt save_file_as.txt
```
* compmain.cpp compresses the file and saves it to the current directory, then automatically extracts it and saves it to *filename_recovered.txt*
**Output:**
```console
File compressed to: song_bitstr.txt
File recovered to song_recovered.txt
===========================================================
song_et_al.txt: 
Size: 
bits: 229526
bytes: 1836208
===========================================================
===========================================================
song_bitstr.txt: 
Size: 
bits: 146526
bytes: 1172208
===========================================================
```



