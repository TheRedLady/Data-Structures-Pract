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
class LinkedList {

private:
	Node<T>* head;
	size_t size;

	Node<T>* copyList(Node<T>*);
	void destroyList();

	T& getAt(size_t);

public:

	LinkedList();
	LinkedList(LinkedList const &);
	LinkedList& operator=(LinkedList const &);
	~LinkedList();

 	bool isEmpty() const;

	void append(T const &);
	void prepend(T const &);
	void insertAt(size_t, T const &);
	
	void remove(T const &);
	void removeAt(size_t);

	T operator[](size_t) const;
	T& operator[](size_t);

	void print() const;

};

template <typename T>
LinkedList<T>::LinkedList() {
	this->head = nullptr;
	this->size = 0;
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList const & other){
	this->head = this->copyList(other.head);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList const & other){
	if(this != &other){
		this->destroyList();
		this->head = this->copyList(other.head);
	}

	return *this;
}

template <typename T>
LinkedList<T>::~LinkedList(){
	this->destroyList();
}

template <typename T>
void LinkedList<T>::prepend(T const & data) {
	this->head = new Node<T>(data, this->head);
	this->size++;
}

template <typename T>
void LinkedList<T>::append(T const & data){
	if(this->head){

		Node<T>* current = this->head;

		while(current->next){
			current = current->next;
		}
		current->next = new Node<T>(data, nullptr);
		this->size++;
	}
	else {

		this->prepend(data);
	}

}

template <typename T>
void LinkedList<T>::insertAt(size_t index, T const & data){
	if(index > this->size){
		throw length_error("Index out of bounds.");
	}

	if (index == this->size)
	{
		this->append(data);
		return;
	}

	if(!index){
		this->prepend(data);
		return;
	}

	Node<T>* current = this->head;
	Node<T>* previous = nullptr;

	while(index--){
		previous = current;
		current = current->next;
	}

	previous->next = new Node<T>(data, current);
	this->size++;
}

template <typename T>
void LinkedList<T>::removeAt(size_t index){
	//cout << "Size: " << this->size <<endl;
	if(index >= this->size){	
		throw length_error("Index out of bounds.");
	}

	if(!index){
		Node<T>* forDelete = this->head;
		this->head = this->head->next;
		delete forDelete;
		this->size--;
		return;
	}

	Node<T>* current = this->head;
	Node<T>* previous = nullptr;

	while(index--){
		previous = current;
		current = current->next;
	}

	Node<T>* forDelete = current;
	previous->next = current->next;
	delete forDelete;
	this->size--;
}

template <typename T>
void LinkedList<T>::remove(T const & data) {
	Node<T>* forDelete;
	if(this->head->data == data){
		forDelete = this->head;
		this->head = this->head->next;
		delete forDelete;
		this->size--;
		return;
	}

	Node<T>* current = this->head;
	Node<T>* previous = nullptr;
	while(current && current->data != data){
		previous = current;
		current = current->next;
	}

	if(current == nullptr) {
		throw logic_error("No such element in the list!");
	}

	forDelete = current;
	previous->next = current->next;
	delete forDelete;
	this->size--;

}

template <typename T>
T& LinkedList<T>::getAt(size_t index) {
	if(index >= this->size){
		throw length_error("Index out of bounds.");
	}

	Node<T>* current = this->head;
	while(index--){
		current = current->next;
	}
	return current->data;
}

template <typename T>
T LinkedList<T>::operator[](size_t index) const {

	return getAt(index);
}

template <typename T>
T& LinkedList<T>::operator[](size_t index) {

	return getAt(index);
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
	return this->size == 0; // or this->head == nullptr
}

template <typename T>
void LinkedList<T>::destroyList() {

	if(!this->isEmpty()){

		Node<T>* current = this->head;
		Node<T>* forDelete = this->head;

		while(current){
			forDelete = current;
			current = forDelete->next;
			delete forDelete;
		}

		this->head =  nullptr;
		this->size = 0;
	}
}

template <typename T>
Node<T>* LinkedList<T>::copyList(Node<T>* start) {
	if(start == nullptr){
		return nullptr;
	}

	Node<T>* node = new Node<T>(start->data, nullptr);
	node->next = copyList(start->next);
	return node;
}

template <typename T>
void LinkedList<T>::print() const {
	if(this->head){
		Node<T>* current = this->head;
		while(current) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}
	else {
		cout << "List is empty." << endl;
	}

	
}