#include "BTree.h"

#ifndef HUFFMANDECODER_H_
#define HUFFMANDECODER_H_

class HuffmanDecoder{
	void decode(ifstream &tableFile, ifstream &codedFile, ofstream &decodedFile);
public:
	HuffmanDecoder();
	void decode();
};

#endif