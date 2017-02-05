#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

#ifndef BTREE_H_
#define BTREE_H_

struct Node{
	Node *left, *right;
	int data;

	Node(const int& d, Node *l, Node *r) :left(l), right(r), data(d){}
	Node() :left(NULL), right(NULL){}
};

struct Leaf : public Node{
	char str;

	Leaf() : Node() {}
	Leaf(char _data, const int& d, Node* l, Node* r) : Node(d, l, r), str(_data) {}
};

struct compare{
	bool operator()(Node* l, Node* r){
		return (l->data > r->data);
	}
};

class BTree{
private:
	Node* root;
	Node* decodingPointer;
	void deleteAll(Node* subTreeRoot);
	bool isLeaf(Node* subTreeRoot);
	void makeTree(priority_queue<Node*, vector<Node*>, compare>&);
	bool findCode(const char& x, string &result, Node* subTreeRoot);
	void prettyPrint(int counter, Node* subTreeRoot);
public:
	BTree(map<char, int> &table);
	~BTree();
	string findCode(const char& x);
	void prettyPrint();
	bool consumeSymbol(char c, char &symbol);
};

#endif
