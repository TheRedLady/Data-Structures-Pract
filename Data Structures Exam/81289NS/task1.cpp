#include <iostream>

using namespace std;

struct Node {
	int data;
	Node* next;
};


void push (Node** head, int data){
    Node* nextNode = new Node;
    nextNode->data = data;
    nextNode->next = *head;
    *head = nextNode;
}

bool isPresent (Node *head, int data){
    Node *t = head;
    while (t != NULL){
        if (t->data == data){
            return 1;
        }
        t = t->next;
    }
    return 0;
}

Node *obedinenie(Node *head1, Node *head2){
    Node *result = NULL;
    Node *t1 = head1, *t2 = head2;

// what if t1 has duplicating values 
    while (t1 != NULL){
        push(&result, t1->data);
        t1 = t1->next;
    }
 
    while (t2 != NULL){
        if (!isPresent(result, t2->data)){
            push(&result, t2->data);
        }
        t2 = t2->next;
    }
 
    return result;
}
 
Node *sechenie(Node *head1, Node *head2){
    Node *result = NULL;
    Node *t1 = head1;
 
    while (t1 != NULL){
        if (isPresent(head2, t1->data)){
            push(&result, t1->data);
        }
        t1 = t1->next;
    }
 
    return result;
}
 
void printList (Node *node){
    while (node != NULL){
        cout<<node->data<<endl;
        node = node->next;
    }
}


int main()
{
    Node* list1 = NULL;
    Node* list2 = NULL;

    push (&list1, 12);
    push (&list1, 5);
    push (&list1, 12);
    push (&list1, 65);
 
    push (&list2, 124);
    push (&list2, 5);
    push (&list2, 16);
    push (&list2, 2);

    Node* listsUnion = NULL;
    Node* listsSection = NULL;
    listsUnion = obedinenie(list1, list2);
    listsSection = sechenie(list1, list2);


    cout<<"list1:"<<endl;
    printList(list1);
    cout<<"list2:"<<endl;
    printList(list2);
    cout<<"obedinenie:"<<endl;
    printList(listsUnion);
    cout<<"sechenie:"<<endl;
    printList(listsSection);

    return 0;
}
