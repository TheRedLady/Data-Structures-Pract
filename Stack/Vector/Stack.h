#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Stack {

private:
	vector<T> vec;

public:
	Stack();

	T peek() const;
	bool isEmpty() const;
	void push(const T&);
	T pop();
};

template <typename T>
Stack<T>::Stack() {}

template <typename T>
bool Stack<T>::isEmpty() const{
	return !vec.size();
}

template <typename T>
void Stack<T>::push(const T& elem){
	vec.push_back(elem);
}

template <typename T>
T Stack<T>::pop(){
	T elem = vec.back();
	vec.pop_back();
	return elem;
}

template <typename T>
T Stack<T>::peek() const {
	return vec.back();
}