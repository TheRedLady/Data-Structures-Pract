#include <iostream>
#include <stack>

using namespace std;


void insert(stack<int>* s, int x) {
    if (!s->empty()) {  
        int y = s->top();
        if (x < y) {
            s->pop();
            insert(s, x);
            s->push(y);
        } else {
            s->push(x);
        }
    } else {
        s->push(x); 
    }
}


void sort(stack<int> *s) {
    if (!s->empty()) {
        int x = s->top();
        s->pop();
        sort(s);
        insert(s, x);
    }
}



int main(){

	stack<int> testStack;
	testStack.push(21);
	testStack.push(12);
	testStack.push(53);
	testStack.push(1);
	cout<<"Before sort:"<<endl;
	for (stack<int> tmp = testStack; !tmp.empty(); tmp.pop())
        cout << tmp.top() <<endl;

	sort(&testStack);
	cout<<"After sort:"<<endl;

	for (stack<int> tmp = testStack; !tmp.empty(); tmp.pop())
        cout << tmp.top() <<endl;
	

}
