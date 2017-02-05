#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;


struct Node
{
    int data;
    Node *left,*right;
    Node();
    Node(const int d,Node *l,Node* r):data(d),left(l),right(r){}
};

///Zadacha 1
int findMax(Node *subTreeRoot)
{
    if(subTreeRoot->right == nullptr)
        return subTreeRoot->data;

    findMax(subTreeRoot->right);
}

int findMin(Node *subTreeRoot)
{
    if(subTreeRoot->left == nullptr)
        return subTreeRoot->data;

    findMin(subTreeRoot->left);
}


///Zadacha 2 Izkliuchitelno neoptimizirana!
/*!
vector<int> sameElem(Node *root1,Node *root2)
{
    vector<int> result;
    return sameElem(root1, root2, result);
}

vector<int> sameElem(Node *root1,Node *root2, vector<int>& result)
{

    if(root1 == nullptr)
        return rezult;
    sameElem()
}
*/

bool traverseFinder(int x, Node *subTreeRoot)
{
    if(subTreeRoot->data == x)
        return true;

    if(subTreeRoot == nullptr)
        return false;

    if(subTreeRoot->left !=nullptr)
        traverseFinder(x,subTreeRoot->left);
    if(subTreeRoot->right == nullptr)
        traverseFinder(x,subTreeRoot->right);

    return false; ///za vseki sluchai :D
}

void sameElem(Node *root1,Node *root2)
{

    if(root1 == nullptr)
        return;

    if(traverseFinder(root1->data, root2))
        cout << root1->data;

    if(root1 -> left != nullptr)
        sameElem(root1->left,root2);
    if(root1 -> right != nullptr)
        sameElem(root1->right,root2);

    return;
}




///Zadacha 3
vector<int> push1(int x, vector<int> vec)
{
    vector<int> result;
    ///za obrushtaneto

    result.push_back(x);
    for(int i = 1 ; !vector.end() ; i++)
    {
        result.push_back(vec[i-1]);
    }

    result.push_back(x);

    return result;
}

vector<int> push2(int x, vector<int> vec, int len1)
{
    vector<int> result;
    ///za obrushtaneto

    result.push_back(x);
    for(int i = 1 ; !vector.end() ; i++)
    {
        result.push_back(vec[i-1]);
    }

    result.push_back(x);

    return result;
}



///Zadacha 4
///zabravih funkciite za rabota s file osven za proverka dali e prazen file-a
void allUsed(ostream& file)
{
    map<string, int> words;
    string crr;
    char c;
    while(!is_empty(file))
    {
        c = cin.peek();
        if(c != '\n' || c != '\t' || c != ' ' || c != ', ' || c != '. ' || c != '! ' || c != '?')
            crr.push_back(c);
        else
        {
            if(crr.length() != 0)
            {
                if(words.find(crr))
                    words[crr] += 1;
                else
                    words.insert(crr) = 0;
            }

            crr = "";
        }
    }

    return mostUsed(words);
}

void mostUsed(map<string, int> words)
{
    string result[9];
    int maxf = 0;
    string name;
    for(int i = 0 ; i <= 9 ; i++)
    {
        for(map<string,int>::iterator it = words.begin() ; it != words.end() ; ++it)
        {
            if(it->second > maxf)
            {
                maxf = it -> second;
                name = it->first;
            }
        }
        result[i] = name;
        words.erase(name);
    }

    for(int i = 0 ; i <= 9 ; i++)
    {
        cout << result[i];
    }
}





int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
