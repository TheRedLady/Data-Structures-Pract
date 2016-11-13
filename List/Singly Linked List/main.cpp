#include <iostream>
#include "linkedlist.h"


int main(){

	LinkedList<int> test;
	test.print();
	int index = 5;
	while(index--){
		test.append(index); 
	} 
	test.print(); // 4 3 2 1 0

	LinkedList<int> testCopy(test);
	testCopy.print(); // 4 3 2 1 0

	index = 5;
	while(index--){
		testCopy.prepend(index);
	}
	testCopy.print(); // 0 1 2 3 4 4 3 2 1

	LinkedList<int> testAssignment;
	cout << testAssignment.isEmpty() << endl; // 1
	testAssignment = testCopy;
	testAssignment.print(); // 0 1 2 3 4 4 3 2 1 0

	test[0] = 13;
	test.print(); // 13 3 2 1 0
	cout << test[0] << endl; // 13
	cout << test.isEmpty() << endl; // 0
	
	test.insertAt(0, 55); 
	test.print(); // 55 13 3 2 1 0
	test.insertAt(5, 65);
	test.print(); // 55 13 3 2 1 65 0

	test.remove(55); 
	test.print(); // 13 3 2 1 65 0
	test.removeAt(5);
	test.print(); // 13 3 2 1 65
	test.removeAt(0);
	test.print(); // 3 2 1 65 

	return 0;
}