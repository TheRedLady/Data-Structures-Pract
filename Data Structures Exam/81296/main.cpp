#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <assert.h>
using namespace std;

struct node {
	int data;
	node* next;

	node(): next(NULL) {}
	node(int data,node* next): data(data), next(NULL) {}
};
void f1(node* head1,node*head2)
{
    map<int,bool> mp;
    node*current1=head1;
    while(current1!=NULL)
    {
        mp[current1->data]=true;
        current1=current1->next;
    }
    node* current2=head2;
    while(current2!=NULL)
    {
        if(mp.find(current2->data)==mp.end())
        {
            cout<<current2->data;
        }
        current2=current2->next;
    }
// a second map is not necessary 
    map<int,bool> mp2;
    node*c2=head2;
     while(c2!=NULL)
    {
        mp2[current1->data]=true;
        c2=c2->next;
    }
    node* c1=head1;
    while(c1!=NULL)
    {
        if(mp.find(c1->data)==mp2.end())
        {
            cout<<c1->data;
        }
        c1=c1->next;
    }
}
void intersection(node* head1,node*head2)
{
     map<int,bool> mp;
    node*current1=head1;
    while(current1!=NULL)
    {
        mp[current1->data]=true;
        current1=current1->next;
    }
    node* current2=head2;

    while(current2!=NULL)
    {
        if(mp.find(current2->data)!=mp.end())//ako go nameri ne dostiga do end sledovatelno elementa e i vuv 2riq spisuk \
            //i v takuv sluchai go printim
        {
            cout<<current2->data;
        }
        current2=current2->next;
    }

}
class list {
private:
	node*head;
	node *curr;
	node *temp;
	node *last;
public:
    list()
	{
		head = NULL;
		curr = NULL;
		temp = NULL;
	}
	void addFront( int addData)
	{
		node *n = new node(addData,head);
		head = n;
		if (last == NULL)
			last = head;
		assert(head != NULL);
	}
	void addEnd( int addData)
	{
		node *n = new node(addData, NULL);
		if (head == NULL)
        {
			addFront(addData);
		}
		else {
			last->next = n;
			last = last->next;
		}
	}

};
int main()
{
    list l;
    l.addEnd(2);
    l.addEnd(4);
    l.addEnd(6);

    return 0;
}













#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <assert.h>
using namespace std;

template <class T>
struct node {
	T data;
	node<T> *left;
	node<T> *right;
	node() :left(NULL), right(NULL) {}
	node(const T d, node<T> *l, node<T> *r) :data(d), left(l), right(r) {}
};
template <class T>
class tree{
private:
    node<T>* root;
public:
    tree():root(NULL){}
    void addNode(node<T>* &subTreeRoot,const T& x)
	{
		if (subTreeRoot == NULL)
		{
			subTreeRoot=new node<T>(x, NULL, NULL);
		}
		else
		{
			if (x < subTreeRoot->data)
			{
				addNode(subTreeRoot->left, x);
			}
			else if (x>subTreeRoot->data)
			{
				addNode(subTreeRoot->right, x);
			}
		}
	}
	 void swap(int &a, int &b)
    {
        int temp = a;
        a = b;
        b = temp;
    }
    node<T>* find(node<T>* ptr,T x)
    {
        if(ptr==NULL) return NULL;
        if(ptr->data==x) return ptr;
        else
        {
            if(x<ptr->data)
            {
                find(ptr->left,x);
            }
             if(x>ptr->data)
            {
                find(ptr->right,x);
            }
        }
    }
    node<T>* find(T x)
    {
        find(root,x);
    }
	void changeData(T data1,T data2)
	{
	    changeData(root,data1,data2);
	}
	void changeData(node<T>* &ptr,T data1,T data2)
	{
	    if(ptr==NULL) return;

	    node<T>* ptr1=find(data1);
	    node<T>* ptr2=find(data2);
	    swap(ptr1->data,ptr2->data);
	}

    void findError(node<T>* ptr,T rootData)
    {
	// handles only errors in consecutive nodes
        assert(ptr!=NULL);
        if(ptr->left!=NULL&&ptr->left->data<rootData)
        {

            findError(ptr->left,ptr->left->data);
        }
        if(ptr->right!=NULL&&ptr->right->data>rootData)
        {
            findError(ptr->right,ptr->right->data);
        }


        if(ptr->left!=NULL&&rootData<ptr->left->data)
        {
            swap(rootData,ptr->left->data);
	    // only one error is sought 
            if(ptr->left!=NULL)
            {
                findError(ptr->left,ptr->left->data);
            }

        }

        if(ptr->right!=NULL&&rootData>ptr->right->data)
        {

            swap(rootData,ptr->right->data);
            if(ptr->right!=NULL)
            {
                findError(ptr->right,ptr->right->data);
            }

        }
    }
    void findError()
    {
         findError(root,root->data);
    }

 void addNode(const T& x)
 {
     addNode(root,x);
 }
 void print(node<T> * subTreeRoot)const
	{
		if (subTreeRoot == NULL)
		{
			return;// kakvo pravi??
		}
		if (subTreeRoot != NULL)
		{
			cout << subTreeRoot->data << " ";
			print(subTreeRoot->left);
			print(subTreeRoot->right);
		}
	}
	void print()
	{
	    print(root);
	}
};
int main()
{
    tree<int> t;
    t.addNode(5);
    t.addNode(10);
    t.addNode(2);
    t.print();
    cout<<endl;
    t.changeData(5,10);
    t.print();
    cout<<endl;
    t.findError();
    t.print();

   //return 0;
}








#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <assert.h>
using namespace std;
void print(stack<int> s)
{
    while(!s.empty())
    {
        cout<<s.top()<<" ";
        s.pop();
    }
    cout<<endl;
}
int getMax(stack<int> s)
{
	stack<int> s2;
	int max = s.top();
	while (!s.empty())
	{
		if (s.top() > max)
		{
			max = s.top();
		}
		else
		{
			s2.push(s.top());
			s.pop();
		}
	}
	while (!s2.empty())
	{
		s.push(s2.top());
		s2.pop();
	}
	return max;
}
void sortRecursion(stack<int> s)
{
    stack<int> s1
    sortRecursion(s,s1,s.top());
}
void removeElem(stack<int> s,int x)
{
    while(!s.empty())

    {
	// infinite loop
        if(s.top()==x) s.pop()
    }
}
void sortRecursion(stack<int> s,stack<int> s1,int x)
{

    if (s.empty())
	{
		cout<<"empty ";
	}
	// will be called if stack is empty and cause exception
	int temp=getMax(s);
	s1.push(temp);


}

void sort(stack<int> s)
{
    stack<int> newstack;
	if (s.empty())
	{
		cout<<"empty ";
		// there should be a 'return' here
	}
	int x = s.top();
	s.pop();
	newstack.push(x);
	while (!s.empty())
	{
		int temp = s.top();
		s.pop();
		while (!newstack.empty()&&temp>newstack.top())
		{
			s.push(newstack.top());
			newstack.pop();
		}
		newstack.push(temp);
	}
	print(newstack);
}

int main()
{
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    print(s);
    sort(s);
   //return 0;
}
