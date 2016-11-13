#include <vector> 

using namespace std;

template <typename T>
class BinaryHeap {

public:
	BinaryHeap() {}; // good exercise: contructor which takes iterator and turns iterable into heap

	bool isEmpty() const;
	T getMin() const;
	T extractMin();

	int getSize() const;

	void insertElem(T);
	void deleteElem(T);

private:
	vector<T> arr;

	void heapify();
	void heapUp(int);
	void heapDown(int);

	int parent(int);
	int left(int);
	int right(int);

	int findElem(T);
};


template <typename T>
int BinaryHeap<T>::parent(int index){
	return (index - 1) / 2;
}

template <typename T>
int BinaryHeap<T>::left(int index){
	return index * 2 + 1;
}

template <typename T>
int BinaryHeap<T>::right(int index){
	return index * 2 + 2;
}

template <typename T>
int BinaryHeap<T>::findElem(T value)
{
	int index = 0;
	while(index < arr.size())
	{
		if(arr[index] == value)
			return index;
		index++;
	}

	return -1;
}

template <typename T>
T BinaryHeap<T>::getMin() const {
	return arr.front();
}

template <typename T>
int BinaryHeap<T>::getSize() const {
	return arr.size();
}

template <typename T>
T BinaryHeap<T>::extractMin() {
	if(this->isEmpty()){
		throw length_error("No elements in heap.");
	}

	T data;
	if(arr.size() == 1)
	{
		data = arr.front();
		arr.pop_back();
		return data;
	}

	data = arr.front();
	arr.front() = arr.back();
	arr.pop_back();
	heapify();

	return data;
}


template <typename T>
void BinaryHeap<T>::insertElem(T value){
	if(this->isEmpty())
	{
		arr.push_back(value);
		return;
	}

	arr.push_back(value);
	heapUp(arr.size() - 1);
}

template <typename T>
void BinaryHeap<T>::deleteElem(T value){
	if(this->isEmpty())
	{
		throw logic_error("No elements in heap.");
	}

	if(arr.size() == 1){
		arr.pop_back();
	}

	int index = findElem(value);
	if(index == -1){
		throw logic_error("Heap does not contain this element.");
	}

	arr[index] = arr.back();
	arr.pop_back();
	heapDown(index);
}

template <typename T>
void BinaryHeap<T>::heapify() {
	if(arr.size() == 1)
		return;

	for(int i = (arr.size() - 2)/2; i >= 0; --i){
		heapDown(i);
	}
}

template <typename T>
void BinaryHeap<T>::heapUp(int index) {
	while(index != 0 && arr[index] < arr[parent(index)]){
		swap(arr[index], arr[parent(index)]);
		index = parent(index);
	}
}

template <typename T>
void BinaryHeap<T>::heapDown(int index) {
	int child;

	while(index < arr.size()) {
		child = left(index);

		if(child >= arr.size()){
			break;
		}
		if(child + 1 < arr.size() && arr[child] > arr[child + 1]) {
			child = child + 1;
		}
		if(arr[index] > arr[child]){
			swap(arr[index], arr[child]);
			
		}
		index = child;
	}
}

template <typename T>
bool BinaryHeap<T>::isEmpty() const {
	return !arr.size();
}
