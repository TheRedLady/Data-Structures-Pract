#include <iostream>
#include <stack>
#include <map>

using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;
};

template <typename T>
void sameElems(Node * root1, Node * root2) {
	map<T, bool> elems;
	stack<Node> current;
	current.push_back(root1);
	while (!current.empty()) {
		Node * currentNode = current.top();
		// or just elems[currentNode->data] = true/false
		elems.insert(currentNode->data);
		current.pop();
		if (currentNode->left != nullptr) {
			current.push_back(currentNode->left);
		}
		// small error - current.top() should be currentNode
		if (current.top()->right != nullptr) {
			current.push_back(currentNode->right);
		}
	}
	current.push_back(root2);
	while (!current.empty()) {
		Node * currentNode = current.top();
		if (!(elems.find(currentNode->data)==elems.end())){
			cout << currentNode->data;
		}
		current.pop();
		if (currentNode->left != nullptr) {
			current.push_back(currentNode->left);
		}
		if (current.top()->right != nullptr) {
			current.push_back(currentNode->right);
		}

	}
}
