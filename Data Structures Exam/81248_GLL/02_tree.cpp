#include <iostream>

using namespace std;

struct Node
{
	int data;
	Node* left;
	Node* right;
	Node(const int& sData) : data(sData), left(nullptr), right(nullptr) {}
	Node(const int& sData, Node* sLeft, Node* sRight) : data(sData), left(sLeft), right(sRight) {}
};

bool hasLeft(const Node* root)
{
	return (root->left != nullptr);
}

bool hasRight(const Node* root)
{
	return (root->right != nullptr);
}

void insertInTree(Node* &root, const int& elem)
{
	if(root == nullptr)
	{
		root = new Node(elem);
	}
	// infinite recursion because of root in ^
	if(elem <= root->data)
	{
		insertInTree(root->left, elem);
	}
	else
	{
		insertInTree(root->right, elem);
	}
}

void reinsertElements(Node* root, Node* newRoot)
{
	insertInTree(newRoot, root->data);
	if(hasLeft(root))
	{
		reinsertElements(root->left, newRoot);
	}
	if(hasRight(root))
	{
		reinsertElements(root->right, newRoot);
	}
}

Node*  fixBrokenTree(Node* root)
{
	Node* newRoot = nullptr;
	if(root != nullptr)
	{
		reinsertElements(root, newRoot);
	}
	return newRoot;
}


int main() {

	Node* mytree = new Node(5);
	insertInTree(mytree, 6);
return 0;


}
