#include "BTree.h"


#ifndef HUFFMANENCODER_H_
#define HUFFMANENCODER_H_

class HuffmanEncoder{
	map<char, string> codeTable(map<char, int> x, BTree &tree);
	void encode(ifstream &file, ofstream &tableFile, ofstream &codedFile);
public:
	HuffmanEncoder();
	void encode();
};

#endif
