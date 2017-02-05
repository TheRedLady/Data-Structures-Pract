#include <iostream>

using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;

	Node(): left(NULL), right(NULL) {}
	Node(int d, Node* l, Node* r): data(d), left(l), right(r) {}
};

void fix(Node* root)
{
    if(root == NULL) return;
    if(root->data > root->left->data && root->data < root->right->data)
    {
        fix(root->left);
        fix(root->right);
    }

    if(root->data > root->left->data && root->data < root->right->data)
    {
        int temp = root->left->data;
        root->left->data = root->right->data;
        root->right>data = temp;
        return;
    }


        if(root->data < root->left->data )
        {
            Node* tempNode = root->left;
            fix(root->right);
        }
    }

    if(root->data > root->right->data)
    {
        int temp = root->right->data;
        root->right->data = tempNode->left->data;
        tempNode->left->data = temp;
    }




int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
