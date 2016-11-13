#include <iostream>
#include "Stack.h"

using namespace std;

int main() {

	Stack<int> test;

	for(int i = 0; i < 5; i++) {
		test.push(i);
	}

	cout << test.isEmpty() << endl; // 0
	cout << test.peek() << endl; // 4

	while(!test.isEmpty()) {
		cout << test.pop() << " ";
	} // 4 3 2 1 0
	cout << endl;

	cout << test.isEmpty() << endl; // 1

	return 0;
}