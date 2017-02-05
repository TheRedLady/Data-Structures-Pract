#include <unordered_map>

using std::unordered_map;

struct Node
{
	int data;
	Node* next;

	Node() : next(nullptr) {}
	Node(int data) : data(data), next(nullptr) {}
	Node(int data, Node* sNext) : data(data), next(sNext) {}
};

void pushBack(Node* first, int elemToAdd)
{
	while(first->next != nullptr)
	{
		first = first->next;
	}
	first->next = new Node(elemToAdd);
}

void copyList(const Node* from, Node* to)
{
	to = new Node(from->data);
	while(from->next != nullptr)
	{
		pushBack(to, from->data);
		from = from->next;
	}
	pushBack(to, from->data);
}

void initialiseIntBoolMapFromList(const Node* first, unordered_map<int, bool> &map)
{
	while(first->next != nullptr)
	{
		map[first->data] = false;
		first = first->next;
	}
	map[first->data] = false;
}

Node* listUnion(const Node* first, const Node* second)
{
	Node* newList = new Node(first->data); //hack
	unordered_map<int, bool> unionElems;

	if(first == nullptr && second == nullptr)
	{
		return newList;
	}
	if(first == nullptr)
	{
		copyList(second, newList);
		return newList;
	}
	else if (second == nullptr)
	{
		copyList(second, newList);
		return newList;
	}
	initialiseIntBoolMapFromList(first, unionElems);
	initialiseIntBoolMapFromList(second, unionElems);
	unionElems[first->data] = true; // hack

	while(first != nullptr)
	{
		if(!unionElems[first->data])
		{
			unionElems[first->data] = true;
			pushBack(newList, first->data);
		}
		first = first->next;
	}
	while(second != nullptr)
	{
		if(!unionElems[second->data])
		{
			unionElems[second->data] = true;
			pushBack(newList, second->data);
		}
		second = second->next;
	}
	return newList;
}

Node* listIntersection(const Node* first, const Node* second)
{
	Node* newList = nullptr; //hack
	unordered_map<int, bool> intersectionElems;

	if(first == nullptr || second == nullptr)
	{
		return newList;
	}

	initialiseIntBoolMapFromList(first, intersectionElems);
	initialiseIntBoolMapFromList(second, intersectionElems);

	while(first != nullptr)
	{
		if(!intersectionElems[first->data])
		{
			intersectionElems[first->data] = true;
		}
		first = first->next;
	}
	while(second != nullptr)
	{
		if(intersectionElems[second->data])
		{
			if(newList == nullptr) //stupid hack, sorry
			{
				newList = new Node(second->data);
			}
			else
			{
				pushBack(newList, second->data);
			}
		}
		second = second->next;
	}
	if(newList == nullptr)
	{
		newList = new Node(); //stupid hack
	}
	return newList;
}
