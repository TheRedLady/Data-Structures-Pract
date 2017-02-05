#include <iostream>
#include <map>
#include<stack>
#include<vector>
#include <iostream>
#include <fstream>
#include<string>
#include <algorithm>


using namespace std;


struct Node {
	int data;
	Node* left;
	Node* right;

	Node() :left(NULL), right(NULL){}
	Node(int _data) : data(_data),left(NULL), right(NULL){}
};

//task 1
int min(Node* tree,int minimum)
{

    if(tree == NULL)
    {
         return 0;
    }

	// it is a BST!
        if(tree->data<minimum)
        {
            minimum = tree->data;
        }

        min(tree->left,minimum);
        min(tree->right,minimum);

        return minimum;

}

int max(Node* tree,int maximum)
{

    if(tree == NULL)
    {
         return 0;
    }

        if(tree->data>maximum)
        {
            maximum = tree->data;
        }

        min(tree->left,maximum);
        min(tree->right,maximum);

        return maximum;

}//task 1

//task 2
void sameElements (Node* tree1, Node* tree2, map<int,bool> map1)
{
    if(tree1 == NULL || tree2==NULL)
        cout<< "";

    map1[tree1->data]=true;
    map1[tree2->data]=true;

    // cannot be more than one - it is a map
    if(map1.count(tree1->data)>1)
        cout<<tree1->data;

    sameElements(tree1->left,tree2->left, map1);
    sameElements(tree1->right,tree2->right, map1);

}
//task 2
vector<int> intoVector(stack<int> s1, stack<int> s2)
{
  vector<int> myVector;

  while(!s1.empty())
  {
     myVector.push_back(s1.top());
     s1.pop();
  }
  int size1 = s2.size();
  int arr[size1] ;
  for(int i=size1;i>=0;i--)
  {
     // arr[i]
     arr[size1] = s2.top();
     s2.pop();
  }

  for(int i=0;i<size1;i++)
  {
    myVector.push_back(arr[i]);
  }

  return myVector;

}

void push1(int x, vector<int> v)
{

  vector<int>::iterator it;
  it = v.begin();
  it = v.insert ( it , x );


}
void push2(int x, vector<int> v)
{
    v.push_back(x);

}
void pop1(vector<int> v)
{
  v.erase(v.begin());
}
void pop2(vector<int> v)
{
  v.pop_back();
}
//task 3

//task 4
#include <algorithm>

char toSpace(char s)
{
    if (s == '.' || s == '\t' || s == ',' || s == '!'|| s == ':' || s == '?')
    {
        return ' ';
    }
    return(tolower(s));
}

void mostOccurences(ifstream& infile)
{
  map<string, int> counts;
  string currentWord;

  while(currentWord << infile)
    {
    transform(currentWord.begin(), currentWord.end(), currentWord.begin(), convert);
    counts[currentWord]++;
    currentWord.clear();
    }

  for(map<string,int>::iterator it = counts.begin();it!=counts.end();it++)
  {
   if(counts[it->second]>5)
   {
     cout<<it->second<<" ";
   }
  }


}
int main()
{



return 0;
}
