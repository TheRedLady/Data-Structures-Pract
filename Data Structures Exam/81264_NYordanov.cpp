#include <iostream>
#include <assert.h>
#include <map>
#include <set>

using namespace std;


// TASK 1

struct Node
{
    int data;
    Node* left;
    Node* right;

    Node():data(NULL),left(NULL),right(NULL) {}
    Node(const int& d,Node* l,Node* r) : data(d),left(l),right(r) {}
};

    int minElement(Node* root) const
{
    assert(root != NULL);
    Node* current = root;

    while(current->left != NULL)
    {
        current = current->left;
    }

    return current->data;
}

int maxElement (Node* root) const
{
    assert(root != NULL);
    Node* current = root;

    while(current->right != NULL)
    {
        current = current->right;
    }

    return current->data;
}

// END OF TASK 1



//TASK 2

struct Node
{
    int data;
    Node* left;
    Node* right;

    Node():data(NULL),left(NULL),right(NULL) {}
    Node(const int& d,Node* l,Node* r) : data(d),left(l),right(r);
    };

    map<int,bool> mymap;
    set<int> myset;

    void findFromFirst(Node* root) //adding all elements from the first tree in a map
{
    if(root == NULL)
        return;


    mymap[root->data] = false ; // the value here is default; not important

    findFromFirst(root->left);
    findFromFirst(root->right);

}

void findFromSecond(Node* root) // adding all elements from the second tree in a set
{
    if(root == NULL)
        return;

    myset.insert(root->data);

    findFromSecond(root->left);
    findFromSecond(root->right);
}

void printCommon (Node* root1,Node* root2)
{

    findFromFirst(root1);
    findFromSecond(root2);

    set<int>::iterator it = myset.begin();

    while(it != myset.end())
    {
        if(mymap.find(*it) != mymap.end()) //if a member from the set(2nd tree) is in the map(1st tree) we print it because it is common
        {
            cout<<*it<<endl;
        }
        it++;
    }
}


// END OF TASK 2




// TASK 3

// The idea I will be using is that we  assign two variables :
//(one for each stack) to the opposite ends of the array(the beginning and the end).These variables are working as top of the stack.
//When pushing to "stack1" we will be moving its variable to the right.(Initial value for the var1 will be -1 so when the first elem is pushed it will be at pos 0)
//The same will apply to "stack 2" but its variable(initial value = size) will be moved to the left.
//In case of var1 > var2, there will be a stack overflow.
//When popping we will get the element at position [var1/var2](the last added) and then decrease var1/increase var2 to update the state of the structure.

//I will implement it using a class because it is easier to read,to organize:
//(can use the private data in the methods ; no need to add additional parameters to them)
//and to set initial values via the constructor.


class TwoStacksInArray
{

private:
    int sizeOfArray;
    int varLeftStack;
    int varRightStack;
    int *arr;

public:

    TwoStacksInArray(int arrSize)
    {
        sizeOfArray = arrSize;
        arr = new int[arrSize];

        varLeftStack = -1;
        varRightStack = arrSize;
    }

    void push1(int data)
    {
        if (varLeftStack < varRightStack - 1)
        {
            varLeftStack++;
            arr[varLeftStack] = data;
        }
        else
        {
            cout << "Stack Overflow.Left var is bigger than the right one"<<endl;
        }
    }

    void push2(int data)
    {

        if (varLeftStack < varRightStack - 1)
        {
            varRightStack--;
            arr[varRightStack] = data;
        }
        else
        {
            cout << "Stack Overflow.Left var is bigger than the right one"<<endl;
        }
    }

    int pop1()
    {
        if (varLeftStack >= 0 )
        {
            int crrElement = arr[varLeftStack];
            varLeftStack--;
            return crrElement;
        }
        else
        {
            cout << "Error."<<endl;
        }
    }

    int pop2()
    {
        if (varRightStack < sizeOfArray)
        {
            int crrElement = arr[varRightStack];
            varRightStack++;
            return crrElement;
        }
        else
        {
            cout<<"Error."<<endl;
        }
    }
};

// END OF TASK 3



