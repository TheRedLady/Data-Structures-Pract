#include <iostream>
#include <assert.h>

using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
    Node (Node* l, Node* r, int d): left(l), right(r), data(d) {}
};

int getMinElementInBST(Node* root)
{
    assert(root != NULL);
    while (root -> left != NULL)
        root = root -> left;
    return root -> data;
}

int getMaxElementInBST(Node* root)
{
    assert(root != NULL);
    while (root -> right != NULL)
        root = root -> right;
    return root -> data;
}

int main()
{
    return 0;
}
