#include <iostream>

using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;
};

void minmaxBTree(Node * root) {
	Node * currentMin = root;
	while (currentMin->left != nullptr) {
		currentMin = currentMin->left;
	}
	cout << "Min:" << currentMin->data;

	Node * currentMax = root;
	while (currentMax->right != nullptr) {
		currentMax = currentMax->right;
	}
	cout << "Max:" << currentMax->data;
}