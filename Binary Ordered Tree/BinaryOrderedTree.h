#include <iostream>

using namespace std;

template <typename T>
struct Node {

	T data;
	Node<T>* left;
	Node<T>* right;

	Node()
		:left(nullptr), right(nullptr) {};

	Node(T data)
		:data(data), left(nullptr), right(nullptr) {};

};

template <typename T>
class BOT{

public:
	BOT();
	~BOT();

	void insert(T); // O(log n) 
	void remove(T); // O(log n)

	bool contains(T) const; // O(log n)

	void print() const;

private:
	void printOrdered(Node<T>*) const;
	void insertRec(Node<T>* &, T);
	void deleteTree(Node<T>*&);
	void removeNode(Node<T>*&);

	T getNewValue(Node<T>**);

	int height(Node<T>*) const; // when the argument is the root returns the height of the tree

	Node<T>* root;

};

template <typename T>
BOT<T>::BOT()
	:root(nullptr) {}

template <typename T>
BOT<T>::~BOT() {
	deleteTree(root);
}

template <typename T>
void BOT<T>::deleteTree(Node<T>*& subTree) {
	if (subTree->left == nullptr && subTree->right == nullptr)
	{
		delete subTree;
		subTree = nullptr;
		return;
	}

	if (subTree->left != nullptr)
		deleteTree(subTree->left);
	if (subTree->right != nullptr)
		deleteTree(subTree->right);
}

template <typename T>
bool BOT<T>::contains(T elem) const {
	Node<T>* current = root;
	while (current != nullptr)
	{
		if (current->data == elem){
			return true;
		}

		if (current->data > elem){
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	return false;
}

template <typename T>
void BOT<T>::insertRec(Node<T>*& subTree, T elem) {
	if (subTree == nullptr)
	{
		subTree = new Node<T>(elem);
		return;
	}
	if (subTree->data < elem)
		insertRec(subTree->right, elem);
	else 
		insertRec(subTree->left, elem);
}

template <typename T>
void BOT<T>::insert(T elem) {
	if (contains(elem))
		return;

	if (root == nullptr)
	{
		root = new Node<T>(elem);
		return;
	}

	insertRec(root, elem);
}

template <typename T>
void BOT<T>::removeNode(Node<T>*& start){
	if (start == nullptr)
		return;

	if(start->left == nullptr && start->right == nullptr){
		delete start;
		start = nullptr;
		return;
	}

	Node<T>* temp;

	if(start->left == nullptr) {
		temp = start;
		start = start->right;
		delete temp;
		return;
	}
	if(start->right == nullptr) {
		temp = start;
		start = start->left;
		delete temp;
		return;
	}
	start->data = getNewValue(&start);
}

template <typename T>
T BOT<T>::getNewValue(Node<T>** start){ 
	T data;

	Node<T>** dummy = &((*start)->right);
	while((*dummy)->left != nullptr){
		dummy = &((*dummy)->left);
	}
	
	data = (*dummy)->data;
	removeNode(*dummy);
	return data;
}

template <typename T>
void BOT<T>::remove(T elem) {
	if (root == nullptr || !contains(elem))
		return;

	Node<T>** start = &root;
	while((*start) != nullptr && (*start)->data != elem){
		if((*start)->data < elem){
			start = &((*start)->right);
		}
		else {
			start = &((*start)->left);
		}
	}
	removeNode(*start);
}

template <typename T>
int BOT<T>::height(Node<T>* node) const {
	if (node == nullptr) {
		return 0;
	}

	int heightLeft = height(node->left);
	int heightRight = height(node->right);

	return 1 + (heightRight > heightLeft ? heightRight : heightLeft);
}

template <typename T>
void BOT<T>::print() const {
	if(root == nullptr){
		cout << "Tree is empty." << endl;
	}
	printOrdered(root);
	cout << endl;
}

template <typename T>
void BOT<T>::printOrdered(Node<T>* node) const { // in order traversal
	if(node->left) {
		printOrdered(node->left);
	}
	cout << node->data << " ";

	if(node->right) {
		printOrdered(node->right);
	}
}