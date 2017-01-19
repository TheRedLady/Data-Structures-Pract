#include <iostream>
#include <stack>
using namespace std;

struct Node
{
	int data;
	Node* next;

	Node(): next(nullptr) {}
	Node(int data,Node* next): data(data), next(nullptr) {}
};

bool presentStack (stack<int> st, int data)
{
    while (!st.empty())
    {
        if (st.top()==data)
        {
            return 1;
        }
        st.pop();
    }
    return 0;
}

void unitedLists (Node* first, Node* second)
{
    stack<int> result;

    while (first != nullptr)
    {
        result.push (first->data);
        first=first->next;
    }
    while (second != nullptr)
    {
        if(!presentStack(result, second->data))
        {
            result.push(second->data);
        }
        second=second->next;
    }

}

void intersection (Node* first, Node* second)
{
    stack<int> result;
    while(first!=nullptr)
    {
        if(presentStack(second,first->data))
        {
            result.push(first->data);
        }
        first=first->next;
    }
    while (!result.empty())
    {
        cout<<result.top()<<" ";
        result.pop();
    }

}

int main()
{
    Node* sixth (9,nullptr);
    Node* fifth (8,sixth);
    Node* fourth(7,fifth);
    Node* third(3,fourth);
    Node* second(2,third);
    Node* first(1,second);
    unitedLists(first, fourth);


    return 0;
}
