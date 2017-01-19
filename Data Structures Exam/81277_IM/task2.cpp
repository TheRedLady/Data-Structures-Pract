#include <iostream>
#include <assert.h>
#include <cstring>
#include <fstream>
#include <vector>
#include <iomanip>
#include <limits.h>
#include <stack>

using namespace std;

template<class T>
using mapFn = bool (*)(const T&);

template<class T>
using mapFn2 = T (*)(const T&);

template <class T>
struct Node
{
	Node<T>* left;
	Node<T>* right;
	T data;

	Node(const T& d,Node<T>* l,Node<T>* r): data(d),left(l),right(r){}
	Node():left(NULL),right(NULL){}
};

template <class T>
class BTree
{
private:
	using waitingStep = pair<int,Node<T>*>;
	#define STEP_EXTRACT_ROOT 0
	#define STEP_TRAVERSE_SUBTREE 1


	Node<T>* root;
	Node<T>* copyTree(const Node<T>* subTreeRoot);
	bool add(const T& data,const char* trace, Node<T>*&); /// !!!
	void simplePrint(Node<T>* subTreeRoot) const;
	void deleteAll(Node<T>* subTreeRoot);
   	bool member(const T& data,Node<T>* subTreeRoot) const;
	void mapFunc(mapFn2<T> f,Node<T>* subTreeRoot);
   	int countMembers(Node<T>* subTreeRoot);
   	int countEvens(Node<T>* subTreeRoot);
  	int searchMap(Node<T>* subTreeRoot,mapFn<T> f);
  	int height(Node<T>* subTreeRoot);
  	int countLeaves(Node<T>* subTreeRoot);
  	T& maxLeaf(Node<T>* subTreeRoot,T currentMax);
  	int notLeaves(Node<T>* subTreeRoot);
  	void serialize(Node<T>* subTreeRoot,ostream&) const;
  	void serializeScheme(Node<T>* subTreeRoot,ostream&) const;
  	Node<T>* parseTree(istream& in);
  	void listLeaves(Node<T>* subTreeRoot,vector<T>& v);
  	void findTrace(Node<T>* subTreeRoot,const T& x,string trace);
  	//T findByIndex (Node<T>* subTreeRoot,int index,int counter);
  	void prettyPrint (Node<T>* subTreeRoot,int space);
  	void insertBOT(Node<T>*& subTreeRoot,const T& data);
  	Node<T>* insertedBOT(Node<T>* subTreeRoot,const T& data);
  	T minElement (Node<T>* subTreeRoot) const ;
  	void deleteElement(Node<T>*& subTreeRoot,const T& data);
  	void inorderPrint(Node<T>* subTreeRoot);
  	void preorderPrint(Node<T>* subTreeRoot);
	void postorderPrint(Node<T>* subTreeRoot);
	int calculateTree(Node<T>* subTreeRoot);

	bool isBOT(Node<T>* subTreeRoot,int min,int max);
	void fixErrorInBOT(Node<T>* subTreeRoot);

public:
	class LeftRootRightIterator
	{
		public:
			LeftRootRightIterator (Node<T>* root);
			T& operator * ();
			LeftRootRightIterator& operator ++ ();
			bool operator != (const LeftRootRightIterator& other);

		private:
			stack<waitingStep> operations;
			void unwind();

	};

public:
	BTree();
	BTree (const BTree<T>& other);
	BTree<T>& operator=(const BTree<T>& other);
	~BTree();
	BTree<T>& add(const T& data,const char* trace);
	void simplePrint() const;
	void deleteAll();
	bool member(const T& data) const;
	void mapFunc (mapFn2<T> f);
	int countMembers();
	int countEvens();
	int searchMap(mapFn<T> f);
	int height();
	int countLeaves();
	T& maxLeaf();
	int notLeaves();
	void serialize(ostream&) const;
	void serializeScheme(ostream&) const;
	void deserialize(istream&);
	vector<T> listLeaves();
	string findTrace(const T& x);
	//T findByIndex(int index);
	void prettyPrint();
	BTree<T>& insertBOT(const T& data);
	BTree<T> insertedBOT(const T& data);
	T minElement() const;
	void deleteElement(const T& data);

	void inorderPrint();
  	void preorderPrint();
	void postorderPrint();
	int calculateTree();

	LeftRootRightIterator end ();
	LeftRootRightIterator begin ();

	bool isBOT();
    void fixErrorInBOT();
};

// START WORKING WITH ITERATOR //
template<class T>
BTree<T>::LeftRootRightIterator::LeftRootRightIterator(Node<T>* root)
{
	if(root != NULL)
	{
		operations.push(BTree<T>::waitingStep(STEP_TRAVERSE_SUBTREE,root));
		//unwind осигурява, че на върха на стека
		//има операция за извличане или стекът е празен. Други
		//състояния на стека не са допустими.
		unwind();
	}
}

template<class T>
T& BTree<T>::LeftRootRightIterator::operator * ()
{
	//всички операции с итератора осигуряват, че на върха му
	//има операция за извличане или стекът е празен. Други
	//състояния на стека не са допустими.
	//Възелът на върха на стека е текущо посетения възел
	//при обхождането

	assert(!operations.empty());
	assert(operations.top().first == STEP_EXTRACT_ROOT);
	assert(operations.top().second != NULL);

	return operations.top().second->data;
}

template<class T>
typename BTree<T>::LeftRootRightIterator& BTree<T>::LeftRootRightIterator:: operator ++ ()
{
	//всички операции с итератора осигуряват, че на върха му
	//има операция за извличане или стекът е празен. Други
	//състояния на стека не са допустими.

	assert(!operations.empty());
	//премахва се операцията за извличане, която е на върха на стека.
	//това довежда до продължаване на обхождането към следващите "части"
	//на дървото, или "активиране" на изчакващите под върха на стека операции
	operations.pop();
	//стекът се "доразвива" до достигане на следваща
	//операция за извличане
	unwind();

	return *this;
}

template<class T>
bool BTree<T>::LeftRootRightIterator::operator != (const LeftRootRightIterator& other)
{
	if(operations.empty())
		return !other.operations.empty();

	if(other.operations.empty())
		return !operations.empty();

	//и двата са непразни
	return operations.top() != other.operations.top();
}

template<class T>
void BTree<T>::LeftRootRightIterator::unwind()
{
	//този метод извършва обхождането на чакащите за
	//обхождане указатели към поддървета до момента, в който
	//на върха на стека попадне операция за извличане на елемент. Т.е.
	//обхождането се "развива" до достигане на следващя чакащ
	//за "отпечатване" връх

	if(operations.empty())
		return;

	BTree<T>::waitingStep topOperation = operations.top();
	Node<T>* topNode = topOperation.second;

	while(!operations.empty() && topOperation.first != STEP_EXTRACT_ROOT)
	{
		operations.pop();

		if(topNode->right != NULL)
			operations.push(BTree<T>::waitingStep(STEP_TRAVERSE_SUBTREE,topNode->right));

		operations.push(BTree<T>::waitingStep(STEP_EXTRACT_ROOT,topNode));

		if(topNode->left != NULL)
			operations.push(BTree<T>::waitingStep(STEP_TRAVERSE_SUBTREE,topNode->left));

		topOperation = operations.top();
		topNode = topOperation.second;
	}


}

template<class T>
typename BTree<T>::LeftRootRightIterator BTree<T>::end()
{
	return LeftRootRightIterator(NULL);
}

template<class T>
typename BTree<T>::LeftRootRightIterator BTree<T>::begin()
{
	return LeftRootRightIterator(root);
}


void testIterator ()
{
	BTree<int> t;

	t.insertBOT(59)
	 .insertBOT(23)
	 .insertBOT(68)
	 .insertBOT(190)
	 .insertBOT(41)
	 .insertBOT(67);


	 BTree<int>::LeftRootRightIterator it = t.begin();

	 assert (*it == 23);

	 ++it;
	 ++it;
	 assert (*it == 59);;

	 int count = 0;
	 for (it = t.begin(); it != t.end(); ++it)
	 {
	    cout << "it=" << *it << " count=" << count << endl;
	 	count++;
	 }


	 assert (count == 6);

}

// FINISH WORKING WITH ITERATOR //

template<class T>
BTree<T>::BTree(): root(NULL){}

template<class T>
Node<T>* BTree<T>::copyTree(const Node<T>* subTreeRoot)
{
	if(subTreeRoot == NULL)
		return NULL;

	return new Node<T>(subTreeRoot->data,copyTree(subTreeRoot->left),copyTree(subTreeRoot->right));
}

template<class T>
BTree<T>::BTree(const BTree<T> &other)
{
	root = copyTree(other.root);
}

template<class T>
BTree<T>& BTree<T>::operator = (const BTree<T>& other)
{
	if(this == &other)
		return *this;

	deleteAll(root);
	root = copyTree(other.root);

	return *this;
}

template <class T>
BTree<T>& BTree<T>::add(const T& data,const char* trace)
{
	add(data,trace,root);
	return *this;
}

template <class T>
bool BTree<T>::add(const T& data,const char* trace,Node<T>* &subTreeRoot)
{
	if(subTreeRoot == 0)
	{
		assert(strlen(trace) == 0);
		subTreeRoot = new Node<T>(data,NULL,NULL);
		return true;
	}

	assert(strlen(trace)>0);

	if(trace[0]=='L')
	{
		return add(data,trace+1,subTreeRoot->left);
	}

	assert(trace[0] == 'R');

	return add(data,trace+1,subTreeRoot->right);

	return true;
}

template<class T>
void BTree<T>::simplePrint() const
{
	simplePrint(root);
}

template <class T>
void BTree<T>::simplePrint(Node<T>* subTreeRoot) const
{
	if(subTreeRoot == NULL)
		return;

	cout<<subTreeRoot->data<<" ";
	simplePrint(subTreeRoot->left);
	simplePrint(subTreeRoot->right);

}

template <class T>
void BTree<T>::deleteAll()
{
	deleteAll(root);
}

template <class T>
void BTree<T>::deleteAll(Node<T>* subTreeRoot)
{
	if(subTreeRoot == NULL)
		return;

	deleteAll(subTreeRoot->left);
	deleteAll(subTreeRoot->right);
	delete subTreeRoot;
}

template<class T>
BTree<T>::~BTree()
{
	deleteAll(root);
}

template<class T>
bool BTree<T>::member(const T& data) const
{
	return member(data,root);
}

template<class T>
bool BTree<T>::member(const T& data,Node<T>* subTreeRoot) const
{
	if(subTreeRoot == NULL)
		return false;

	return subTreeRoot->data == data ||
		   member(data,subTreeRoot->left) ||
		   member(data,subTreeRoot->right);
}

template<class T>
void BTree<T>::mapFunc(mapFn2<T> f)
{
	mapFunc(f,root);
}

template<class T>
void BTree<T>::mapFunc(mapFn2<T> f,Node<T>* subTreeRoot)
{
	if(subTreeRoot == NULL)
		return;

	subTreeRoot->data = f(subTreeRoot->data);
	mapFunc(f,subTreeRoot->left);
	mapFunc(f,subTreeRoot->right);
}

int plusOne(const int& i)
{
	return i + 1;
}

int multByTwo(const int& i)
{
	return i*2;
}

template<class T>
int BTree<T>::countMembers()
{
	return countMembers(root);
}

template<class T>
int BTree<T>::countMembers(Node<T>* subTreeRoot)
{
	if(subTreeRoot == NULL)
		return NULL;

	return countMembers(subTreeRoot->left) + countMembers(subTreeRoot->right) + 1;
}

template<class T>
int BTree<T>::countEvens()
{
	return countEvens(root);
}

template<class T>
int BTree<T>::countEvens(Node<T>* subTreeRoot)
{
    if(subTreeRoot == NULL)
		return NULL;

	int res = (subTreeRoot->data % 2 == 0) ? 1:0;

	return res + countEvens(subTreeRoot->left) + countEvens(subTreeRoot->right);
}

template<class T>
int BTree<T>::searchMap(mapFn<T> f)
{
	return searchMap(root, f);
}

template<class T>
int BTree<T>::searchMap(Node<T>* subTreeRoot, mapFn<T> f)
{
	if (subTreeRoot == NULL)
		return 0;

	if (f(subTreeRoot->data))
	{
		return searchMap(subTreeRoot->left, f) + searchMap(subTreeRoot->right, f) + 1;
	}
	else
	{
		return searchMap(subTreeRoot->left, f) + searchMap(subTreeRoot->right, f);
	}
}


bool divByThree(const int& x)
{
	return x % 3 == 0;
}

bool isHundred(const int& x)
{
	return x>=100 && x<=999;
}

template<class T>
int BTree<T>::height()
{
	return height(root);
}

template<class T>
int BTree<T>::height(Node<T>* subTreeRoot)
{
	if(subTreeRoot == NULL)
		return NULL;

	int leftMax = height(subTreeRoot->left);
	int rightMax = height(subTreeRoot->right);

	if(leftMax > rightMax)
        {
            return leftMax + 1;
        }
    else
        {
            return rightMax + 1;
        }

	/*if(height(subTreeRoot->left) > height(subTreeRoot->right))
	{
		return height(subTreeRoot->left) + 1;
	}
	else
	{
		return height(subTreeRoot->right) + 1;
	}*/
}

template<class T>
int BTree<T>::countLeaves()
{
	return countLeaves(root);
}

template<class T>
int BTree<T>::countLeaves(Node<T>* subTreeRoot)
{
	if(subTreeRoot == NULL)
		return NULL;

	if(subTreeRoot->left == NULL && subTreeRoot->right == NULL )
	{
		return 1;
	}

	else
	{
		return countLeaves(subTreeRoot->left) + countLeaves(subTreeRoot->right);
	}
}

template<class T>
T& BTree<T>::maxLeaf()
{
	return maxLeaf(root,0);

}

template<class T>
T& BTree<T>::maxLeaf(Node<T>* subTreeRoot,T currentMax)
{
	if(subTreeRoot == NULL)
		return currentMax;

	if(subTreeRoot->left == NULL && subTreeRoot->right == NULL )
	{
		currentMax = currentMax > subTreeRoot->data ? currentMax : subTreeRoot->data;
	}


	T leftMax = maxLeaf(subTreeRoot->left,currentMax);
	T rightMax = maxLeaf(subTreeRoot->right,currentMax);

	return leftMax > rightMax ? leftMax : rightMax;
}

template<class T>
int BTree<T>::notLeaves()
{
	return notLeaves(root);
}

template<class T>
int BTree<T>::notLeaves(Node<T>* subTreeRoot)
{
	if(subTreeRoot == NULL)
		return NULL;

	if(subTreeRoot->left == NULL && subTreeRoot->right == NULL)
	{
		return 0;
	}
	else
	{
		return notLeaves(subTreeRoot->left) + notLeaves(subTreeRoot->right) + 1;
	}
}

template<class T>
void BTree<T>::serialize(ostream& out) const
{
	serialize(root,out);
	cout<<endl;
}

template<class T>
void BTree<T>::serialize(Node<T>* subTreeRoot,ostream& out) const
{
	if(subTreeRoot == NULL)
	{
		out<<"null"<<" ";
		return;
	}

	out<<subTreeRoot->data<<" ";

	serialize(subTreeRoot->left,out);
	serialize(subTreeRoot->right,out);
}

template<class T>
void BTree<T>::serializeScheme(ostream& out) const
{
	serializeScheme(root,out);
	cout<<endl;
}

template<class T>
void BTree<T>::serializeScheme(Node<T>* subTreeRoot,ostream& out) const
{
if (subTreeRoot == NULL)
	{
		out << "() ";
		return;
	}

	out << "(" << subTreeRoot->data << " ";

	serializeScheme(subTreeRoot->right, out);
	serializeScheme(subTreeRoot->left, out);

	out << ") ";
}


void removeWhite(istream& in)
{
	if(in.peek() <= 32)
		in.get();
}

template<class T>
Node<T>* BTree<T>::parseTree(istream& in)
{
	removeWhite(in);

	if(in.peek() == 'n')
	{
		string dummy;
		in >> dummy;
		assert(dummy == "null");
		return NULL;
	}

	T data;
	in >> data;

	return new Node<T>(data,parseTree(in),parseTree(in));
}

template<class T>
void BTree<T>::deserialize(istream& in)
{
	deleteAll(root);

	root = parseTree(in);
}

template<class T>
vector<T> BTree<T>::listLeaves()
{
	vector<T> v;
	listLeaves(root,v);

	for (int i = 0; i < v.size(); ++i)
	{
		cout<<v[i]<<" ";
	}

	return v;
}

template<class T>
void BTree<T>::listLeaves(Node<T>* subTreeRoot,vector<T>& v)
{
	if(subTreeRoot == NULL)
		return;

	if(subTreeRoot->left == NULL && subTreeRoot->right == NULL)
	{
		v.push_back(subTreeRoot->data);
	}

	listLeaves(subTreeRoot->left,v);
	listLeaves(subTreeRoot->right,v);

}

template<class T>
string BTree<T>::findTrace(const T& x)
{
    string trace = "";
    findTrace(root,x,trace);
    return trace;

}

template<class T>
void BTree<T>::findTrace(Node<T>* subTreeRoot,const T& x,string trace)
{
	if(subTreeRoot == NULL)
		return;


    if(subTreeRoot->data == x)
        {
             cout<<trace;
       	}

	findTrace(subTreeRoot->left,x,trace + "L");
	findTrace(subTreeRoot->right,x,trace + "R");

}

/*template<class T>
T BTree<T>::findByIndex(int index)
{
	return findByIndex(root,index,0);
}
template<class T>
T BTree<T>::findByIndex(Node<T>* subTreeRoot,int index,int counter)
{
	if(subTreeRoot == NULL)
		return NULL;
	if(index == 0)
		return subTreeRoot->data;
	if(counter == index)
		return subTreeRoot->data;
	findByIndex(subTreeRoot->left,index,counter + 2);
	findByIndex(subTreeRoot->right,index,counter + 1);
}*/

template <class T>
void BTree<T>:: prettyPrint()
{
	prettyPrint(root,0);
}

template<class T>
void BTree<T>::prettyPrint(Node<T>* subTreeRoot,int space)
{
	if (subTreeRoot == NULL)
	{
		return;
	}

	if (subTreeRoot->right != NULL)
	{
		prettyPrint(subTreeRoot->right,space+6);
	}

	if (space != 0)
	{
		cout << setw(space) << " ";
	}

	if (subTreeRoot->right != NULL)
	{
		cout << endl << setw(space) << " ";
	}
	cout << subTreeRoot->data;

	if (subTreeRoot->left != NULL)
	{
		cout << setw(space) << " "<<endl;
		prettyPrint(subTreeRoot->left, space + 6);
	}
}

template<class T>
void BTree<T>::insertBOT(Node<T>*& subTreeRoot,const T& data)
{
	if(subTreeRoot == NULL)
	{
		subTreeRoot = new Node<T>(data,NULL,NULL);
		return;
	}

	if(data <= subTreeRoot->data)
	{
		insertBOT(subTreeRoot->left,data);
	}
	else
	{
		insertBOT(subTreeRoot->right,data);
	}
}

template<class T>
BTree<T>& BTree<T>::insertBOT(const T& data)
{
	insertBOT(root,data);
	return *this;
}

template<class T>
BTree<T> BTree<T>::insertedBOT(const T& data)
{
	BTree<T> result;
	result.root = insertedBOT(root,data);

	return result;
}

template<class T>
Node<T>* BTree<T>::insertedBOT(Node<T>* subTreeRoot,const T& data)
{
	if(subTreeRoot == NULL)
		return new Node<T>(data,NULL,NULL);

	if(data > subTreeRoot->data)
	{
		return new Node<T>(subTreeRoot->data,copyTree(subTreeRoot->left),insertedBOT(subTreeRoot->right,data));
	}

	return new Node<T>(subTreeRoot->data,insertedBOT(subTreeRoot->left,data),copyTree(subTreeRoot->right));
}

template<class T>
T BTree<T>::minElement() const
{
	return minElement(root);
}

template<class T>
T BTree<T>::minElement(Node<T>* subTreeRoot) const
{
	assert(subTreeRoot != NULL);
	Node<T>* current = subTreeRoot;

	while(current->left != NULL)
	{
		current = current->left;
	}

	return current->data;
}

template<class T>
void BTree<T>::deleteElement(const T& data)
{
	deleteElement(root,data);
}

template<class T>
void BTree<T>::deleteElement(Node<T>*& subTreeRoot,const T& data)
{
	if(subTreeRoot == NULL) //delete from empty tree;
		return;

	if(subTreeRoot->data == data && subTreeRoot->left == NULL && subTreeRoot->right == NULL) //delete from leaf
	{
		delete subTreeRoot;
		subTreeRoot = NULL;
		return;
	}

	if(data < subTreeRoot->data) //delete from left SubTree;
	{
		deleteElement(subTreeRoot->left,data);
		return;
	}

	if(data > subTreeRoot->data) //delete from right SubTree;
	{
		deleteElement(subTreeRoot->right,data);
		return;
	}

	if(subTreeRoot->right == NULL)
	{
		Node<T>* temp = subTreeRoot;
		subTreeRoot = subTreeRoot->left;
		delete temp;
		return;
	}

	if(subTreeRoot->left == NULL)
	{
		Node<T>* temp = subTreeRoot;
		subTreeRoot = subTreeRoot->right;
		delete temp;
		return;
	}

	T minel = minElement(subTreeRoot->right);
	subTreeRoot->data = minel;
	deleteElement(subTreeRoot->right,minel);

}

template<class T>
void BTree<T>:: inorderPrint()
{
    inorderPrint(root);
}

template<class T>
void BTree<T>:: inorderPrint(Node<T>* subTreeRoot)
{
    if(subTreeRoot == NULL)
        return ;

    if(subTreeRoot->left)
        {
            inorderPrint(subTreeRoot->left);
        }

    cout<<subTreeRoot->data<<" ";

    if(subTreeRoot->right)
        {
            inorderPrint(subTreeRoot->right);
        }
}

template<class T>
void BTree<T>:: preorderPrint()
{
    preorderPrint(root);
}

template<class T>
void BTree<T>:: preorderPrint(Node<T>* subTreeRoot)
{
    if(subTreeRoot == NULL)
        return ;

    if(subTreeRoot->left)
        {
            preorderPrint(subTreeRoot->left);
        }

    if(subTreeRoot->right)
        {
            preorderPrint(subTreeRoot->right);
        }
        cout<<subTreeRoot->data<<" ";
}

template<class T>
void BTree<T>:: postorderPrint()
{
    postorderPrint(root);
}

template<class T>
void BTree<T>:: postorderPrint(Node<T>* subTreeRoot)
{
    if(subTreeRoot == NULL)
        return ;

     cout<<subTreeRoot->data<<" ";

    if(subTreeRoot->left)
        {
            postorderPrint(subTreeRoot->left);
        }


    if(subTreeRoot->right)
        {
            postorderPrint(subTreeRoot->right);
        }
}

template<class T>
int BTree<T>::calculateTree()
{
	return calculateTree(root);
}

template<class T>
int BTree<T>::calculateTree(Node<T>* subTreeRoot)
{
	if(subTreeRoot->left == NULL && subTreeRoot->right == NULL)
	{
		return subTreeRoot->data - '0';
	}

	assert(subTreeRoot->left != NULL && subTreeRoot->right != NULL);

	switch(subTreeRoot->data)
	{
		case '+':
			return calculateTree(subTreeRoot->left) + calculateTree(subTreeRoot->right);
			break;

		case '-':
			return calculateTree(subTreeRoot->left) - calculateTree(subTreeRoot->right);
			break;

		case '*':
			return calculateTree(subTreeRoot->left) * calculateTree(subTreeRoot->right);
			break;

		case '/':
			assert(subTreeRoot->right != 0);
			return calculateTree(subTreeRoot->left) / calculateTree(subTreeRoot->right);
			break;
	}
}

template<class T>
bool BTree<T>::isBOT()
{
	return isBOT(root,INT_MIN,INT_MAX);
}

template<class T>
bool BTree<T>:: isBOT(Node<T>* subTreeRoot,int min,int max)
{
	if(subTreeRoot == NULL)
		return 1;

	if(subTreeRoot->data < min || subTreeRoot->data > max)
		return 0;

	return isBOT(subTreeRoot->left,min,subTreeRoot->data -1) &&
		   isBOT(subTreeRoot->right,subTreeRoot->data+1,max);
}

template <class T>
void BTree<T>::fixErrorInBOT(Node<T>* subTreeRoot)
{
    if (subTreeRoot==NULL)
    {
        return;
    }
    if (subTreeRoot->data<subTreeRoot->left->data)
    {
        Node<T>* temp=subTreeRoot;
        subTreeRoot=subTreeRoot->left;
        subTreeRoot->left=temp;
        return;
    }
    if(subTreeRoot->data>subTreeRoot->right->data)
    {
        Node<T>* temp = subTreeRoot;
        subTreeRoot=subTreeRoot->right;
        subTreeRoot->right=temp;
        return;
    }
    fixErrorInBOT(subTreeRoot->left);
    fixErrorInBOT(subTreeRoot->right);
}

template <class T>
void BTree<T>::fixErrorInBOT()
{
    fixErrorInBOT(root);
}


int main()
{
	BTree<int> tree;
	BTree<int> bot;
	BTree<int> demo;
	BTree<char> calc;

	tree.add(111,"").add(10,"L").add(12,"R").add(15,"LL").add(1,"LR").add(321,"LLL");

	demo.insertBOT(59)
	 .insertBOT(23)
	 .insertBOT(68)
	 .insertBOT(190)
	 .insertBOT(41)
	 .insertBOT(67);

  bot.insertBOT(56)
	 .insertBOT(23)
	 .insertBOT(68)
	 .insertBOT(190)
	 .insertBOT(41)
	 .insertBOT(60)
	 .insertBOT(65)
	 .insertBOT(59);

	 demo.prettyPrint();
	 cout<<endl<<"__________________________________________"<<endl;
     tree.prettyPrint();
	 cout<<endl;

	//bot.prettyPrint();
	cout<<endl;
	//bot.deleteElement(23);
	cout<<endl;
	//bot.prettyPrint();
	cout<<bot.isBOT()<<endl;
	cout<<tree.isBOT()<<endl;

    //tree.fixErrorInBOT(); doesn't work as well :D
    tree.prettyPrint();

	return 0;
}
