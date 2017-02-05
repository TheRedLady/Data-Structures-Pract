#include <iostream>
#include <stack>
using namespace std;

void insertSorted (stack<int>& st, int current)
{
    if (st.empty()||current>st.top())
    {
        st.push(current);
        return;
    }
    int temp=st.top();
    st.pop();
    insertSorted(st,current);
    st.push(temp);
}

// pass by reference
void sortStack (stack<int>& st)
{
    if (!st.empty())
    {
        int temp = st.top();
        st.pop();
        sortStack(st);
        insertSorted(st,temp);
    }
}

int main()
{
    stack<int> st;
    st.push(3);
    st.push(7);
    st.push(10);
    st.push(4);
    st.push(5);
//    print(st);
    cout<<endl;
    // doesn't work because you are not changing the stack
    sortStack(st); //doesn't work, no clue why
    while(!st.empty()) {
	cout << st.top() << endl;
	st.pop();
    }

    return 0;
}
