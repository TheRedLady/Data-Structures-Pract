#include <iostream>
#include "BinaryHeap.h"

int main()
{

	BinaryHeap<int> minHeap;

	minHeap.insertElem(15);
	minHeap.insertElem(23);
	minHeap.insertElem(4);
	minHeap.insertElem(5);
	minHeap.insertElem(2);
	minHeap.insertElem(0);
	minHeap.insertElem(-1);

	cout << minHeap.isEmpty() << endl; // 0

	cout << minHeap.getMin() << endl; // -1

	while(!minHeap.isEmpty()) {
		cout << minHeap.extractMin() << " ";
	} // -1 0 2 4 5 15 23
	cout << endl;

	cout << minHeap.isEmpty() << endl; // 1

	return 0;
}