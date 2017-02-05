#include "BTree.h"
#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

BTree::~BTree(){
	deleteAll(root);
};

void BTree::prettyPrint(){
	prettyPrint(0, root);
}

void BTree::prettyPrint(int counter, Node* subTreeRoot)
{
	if (subTreeRoot == NULL)
		return;

	prettyPrint(counter + 1, subTreeRoot->right);

	for (int i = 0; i < counter; ++i)
		cout << "\t";
	cout << (subTreeRoot->data) << endl;
	if (isLeaf(subTreeRoot)){
		for (int i = 0; i < counter; ++i)
			cout << "\t";
		cout << (((Leaf*)subTreeRoot)->str) << endl;
	}

	prettyPrint(counter + 1, subTreeRoot->left);
}

BTree::BTree(map<char, int> &table){
	priority_queue<Node*, vector<Node*>, compare> queue;
	for (map<char, int> ::iterator it = table.begin(); it != table.end(); it++){
		Node *node = new Leaf(it->first, it->second, NULL, NULL);
		queue.push(node);
	}

	makeTree(queue);
}

void BTree::makeTree(priority_queue<Node*, vector<Node*>, compare> &queue){
	
	while (queue.size() > 1){
		Node* node1 = queue.top();
		queue.pop();
		Node* node2 = queue.top();
		queue.pop();

		int result = node1->data + node2->data;
		Node* newNode = new Node(result, node1, node2);

		queue.push(newNode);
	}

	root = queue.top();
	queue.pop();
	decodingPointer = root;
}


void BTree::deleteAll(Node *subTreeRoot){
	if (subTreeRoot == NULL)
		return;

	deleteAll(subTreeRoot->left);
	deleteAll(subTreeRoot->right);
	delete subTreeRoot;
}

string BTree::findCode(const char& symbol){
	if (isLeaf(root)){
		Leaf* leaf = (Leaf*)root;
		if (leaf->str == symbol)
			return "0";
	}

	string result = "";
	if (findCode(symbol, result, root))
		return result;

	else return "";
}

bool BTree::findCode(const char& symbol, string &result, Node *subThreeRoot)
{
	if (subThreeRoot == NULL)
		return false;

	if (isLeaf(subThreeRoot))
	{
		Leaf* leaf = (Leaf*)subThreeRoot;
		if (leaf->str == symbol)
			return true;

		else return false;
	}
	else
	{
		bool inLeftSubTree = findCode(symbol, result.append("0"), subThreeRoot->left);
		if (inLeftSubTree)
			return true;
		else{
			result.pop_back();
		}

		bool inRightSubTree = findCode(symbol, result.append("1"), subThreeRoot->right);
		if (inRightSubTree)
			return true;
		else{
			result.pop_back();
		}
	}

	return false;
}

bool  BTree::isLeaf(Node* subTreeRoot){
	return (subTreeRoot != NULL && subTreeRoot->left == NULL && subTreeRoot->right == NULL) ? true : false;
}

bool BTree::consumeSymbol(char symbol, char &character){
	if (symbol == '0')
		decodingPointer = decodingPointer->left;

	if (symbol == '1')
		decodingPointer = decodingPointer->right;

	if (!isLeaf(decodingPointer))
		return false;
	else{
		Leaf* leaf = (Leaf*)decodingPointer;
		character = leaf->str;
		decodingPointer = root;
		return true;
	}
}