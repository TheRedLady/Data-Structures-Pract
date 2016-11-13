#include <iostream>

using namespace std;

template <typename T>
struct Node{
	T data;
	Node* next;

	Node(): 
		data(NULL), next(nullptr){}

	Node(T data, Node<T>* next):
		data(data), next(next){}

};

template <typename T>
class Stack {

private:
	Node<T>* top;
	size_t size;

	Node<T>* copyStack(Node<T>*);
	void destroyStack();

public:

	Stack();
	Stack(Stack const &);
	Stack& operator=(Stack const &);
	~Stack();

 	bool isEmpty() const;
 	T peek() const;
 	void push(T const &);
	T pop();

};

template <typename T>
Stack<T>::Stack():
	top(nullptr), size(0) {}

template <typename T>
Stack<T>::Stack(Stack const & other):
	top(nullptr), size(0) {
	this->top = this->copyStack(other.top);
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack const & other){
	if(this != &other){
		this->destroyStack();
		this->top = this->copyStack(other.top);
	}

	return *this;
}

template <typename T>
Stack<T>::~Stack(){
	this->destroyStack();
}

template <typename T>
bool Stack<T>::isEmpty() const {
	return this->top == nullptr;
}

template <typename T>
T Stack<T>::peek() const {
	return this->top->data;
}

template <typename T>
void Stack<T>::push(T const & data) {
	this->top = new Node<T>(data, this->top);
}

template <typename T>
T Stack<T>::pop() {
	if(this->top == nullptr) {
		throw logic_error("No elements in stack.");
	}

	Node<T>* forDelete = this->top;
	T data = forDelete->data;
	this->top = this->top->next;
	delete forDelete;
	return data;
}

template <typename T>
void Stack<T>::destroyStack() {

	while(!this->isEmpty()) {
		this->pop();
	}

	this->top =  nullptr;
}

template <typename T>
Node<T>* Stack<T>::copyStack(Node<T>* start) {
	if(start == nullptr){
		return nullptr;
	}

	Node<T>* node = new Node<T>(start->data, nullptr);
	node->next = copyStack(start->next);
	return node;
}