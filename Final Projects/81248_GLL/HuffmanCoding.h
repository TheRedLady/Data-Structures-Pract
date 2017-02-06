#ifndef __HUFFMAN_CODING__
#define __HUFFMAN_CODING__

#include "HuffmanTree.h"
#include "FileIOProcessing.h"
#include <limits>

map<char, int> mapCharOccurences(const string& text);
int writeOccurencesToFile(unordered_map<char, int> occurences, const string& filename);

map<char, int> rebuildOccurencesMap(const string& text);
int numberOfDigitsOfNumber(unsigned int num);
int calculateByteArrayStart(const string& text, int letterCount);
int readNumberFromStart(const string& byteArray);

int encodeFile(const string& input, const string& output);
int decodeFile(const string& input, const string& output);

#endif
