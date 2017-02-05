#include <iostream>

using namespace std;

struct Node {
	int data;
	Node* next;

	Node(): next(NULL) {}
	Node(int data, Node* n): data(data), next(n) {}
};

Node* union_(Node* new_n,Node* n1, Node* n2)
{
    if(n1 != NULL && n2 != NULL)
    {
        if(n1->data != n2->data)
        {
            return new_n = new Node(n1->data, new Node(n2->data, union_(new_n->next->next, n1->next, n2->next)));

        }

        else
        {
           return new_n = new Node(n1->data, union_(new_n->next, n1->next, n2->next));

        }


    }

    if(n1 == NULL)
    {
        return new_n = new Node(n2->data, union_(new_n->next, NULL, n2-> next));

    }

    if(n2 == NULL)
    {

        return new_n = new Node(n1->data, union_(new_n->next, n1->next, NULL));
    }

    return NULL;


}

Node* intersection (Node* new_n, Node* n1, Node* n2)
{
    if(n1 != NULL && n2 != NULL)
    {
        if(n1->data != n2->data) intersection(new_n, n1->next, n2->next);

        else
        {
            new_n = new Node(n1->data, NULL);
            intersection(new_n->next, n1->next, n2->next);
        }

    }

    return new_n;

}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
