#ifndef __HUFFMAN_TREE__
#define __HUFFMAN_TREE__

#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include <iostream>
#include <fstream>
#include <map>

using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;
using std::string;
using std::priority_queue;
using std::pair;
using std::ofstream;
using std::map;

struct Node
{
	char character;
	int occurenceCount;
	Node* left;
	Node* right;
	Node(const char& sCharacter, const int& sOccurenceCount, Node* sLeft, Node* sRight);
};

class GreaterNodeComparison
{
public:
	bool operator() (const Node* lhs, const Node* rhs);
};

bool hasLeft(const Node* root);
bool hasRight(const Node* root);
bool isLeaf(const Node* root);

void printTree(const Node* root);
void graphDotPrint(const Node* root, string filename);
void graphDotPrintTree(const Node* root, ofstream& file, int id);

void deleteTree(Node* root);
void deleteTreeNodes(Node* root);
Node* buildTreeFromMap(const map<char,int>& mapping);

string encodeCharacter(const Node* tree, const char& character);
unordered_map<char, string> charToBinaryMapping(const Node* root, const map<char, int>& occurences);
string encodeString(const Node* tree, const string& originalString, const unordered_map<char, string>& mapping);

char decodeFirstCharacter(const Node* tree, const string& encodedString);
string decodeString(const Node* tree, const string& encodedString, const int& stringLength);

#endif
