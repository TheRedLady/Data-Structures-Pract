#include <iostream>

using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;
};

void fixTree(Node *root){
	if(root->left->data > root->right->data){
		Node *tmp = root->right;
        root->right = root->left;
        root->left = tmp;
    }else{
    	fixTree(root->left);
    	fixTree(root->right);
    }
}