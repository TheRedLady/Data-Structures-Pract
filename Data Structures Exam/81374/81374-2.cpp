#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
    Node (Node* l, Node* r, int d): left(l), right(r), data(d) {}
};

void printBSTIntersections(Node* firstRoot, Node* secondRoot)
{
    if ((firstRoot == NULL) || (secondRoot == NULL)) return;
    if (firstRoot -> data == secondRoot -> data)
    {
        cout << firstRoot -> data << endl;
        printBSTIntersections(firstRoot -> left, secondRoot -> left);
        printBSTIntersections(firstRoot -> right, secondRoot -> right);
        return;
    }
    if (firstRoot -> data > secondRoot -> data) swap(firstRoot, secondRoot);
    printBSTIntersections(firstRoot -> right, secondRoot);
    printBSTIntersections(firstRoot, secondRoot -> left);
}

void getSortedElementsOfTree(Node* root, vector <int> &elements)
{
    if (root == NULL)
        return;
    getSortedElementsOfTree(root -> left, elements);
    elements.push_back(root -> data);
    getSortedElementsOfTree(root -> left, elements);
}

void printBSTIntersectionsUsingExtraMemory(Node* firstRoot, Node* secondRoot)
{
    vector <int> firstTreeElements, secondTreeElements;
    getSortedElementsOfTree(firstRoot, firstTreeElements);
    getSortedElementsOfTree(secondRoot, secondTreeElements);
    int ind1 = 0, ind2 = 0;
    while ((ind1 < firstTreeElements.size()) && (ind2 < secondTreeElements.size()))
    {
	// why use indices - they may not be consecutive
        if (firstTreeElements[ind1] == secondTreeElements[ind2])
        {
            cout << firstTreeElements[ind1] << endl;
            ++ind1;
            ++ind2;
        }
        else if (firstTreeElements[ind1] < secondTreeElements[ind2]) ind1++;
        else ind2++;
    }
}

int main()
{
    return 0;
}
