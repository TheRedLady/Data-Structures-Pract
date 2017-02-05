#include <iostream>
#include <map>
#include <stack>
#include <string.h>
#include<vector>

using namespace std;
//task1
struct Node {
	int data;
	Node* next;

	Node(): next(NULL) {}
	Node(int d): data(d), next(NULL) {}
	Node(int d, Node* n){
        data = d;
        next = n;
	}
};
//task2
struct NodeT {
	int data;
	NodeT* left;
	NodeT* right;
	NodeT(int d){
        data = d;
        left = NULL;
        right = NULL;
    }
    NodeT(int d, NodeT*l, NodeT* r){
        data = d;
        left = l;
        right = r;
    }
};

void intersect(Node* fst, Node* snd){

    map<int, int> a;
    while(fst->next != NULL){
        a[fst->data]=fst->data;
        fst = fst->next;
    }

    while(snd->next != NULL){
        if(a.count(snd->data)>0){
            cout<<snd->data<<" ";
        }
        snd = snd->next;
    }


}

void union1(Node* fst, Node* snd){

    map<int, int> a;
    while(fst->next != NULL){
        a[fst->data]=fst->data;
        fst = fst->next;
    }

    while(snd->next != NULL){
       a[snd->data]=snd->data;
        snd = snd->next;
    }

    for(map<int,int>::iterator it = a.begin(); it !=a.end(); it++)
    {
        // no need for dereferencing
        cout<<it->first<<" ";

    }
}

void fixMistake(NodeT * root){

    if(root == NULL){
        return;

    }
    // would only work when error is in consecutive nodes 
    if(root->data<root->left->data){
        int temp = root->data;
        root->data=root->left->data;
        root->left->data = temp;
        return;
    }
    if(root->data>root->right->data){
        int temp = root->data;
        root->data=root->right->data;
        root->right->data = temp;
        return;
    }
    fixMistake(root->left);
    fixMistake(root->right);



}
//task3
stack<int> sortStack(stack<int> s){
    stack<int> result;
    while(!s.empty()){
        int fst = s.top();
        s.pop();
        int snd = s.top();

        if(fst < snd){
            s.pop();
            s.push(fst);
            result.push(snd);
            // sortStack returns stack
            result.push(sortStack(s));


        }
        if(fst >= snd){
            result.push(s.top());
            s.pop();
            result.push(sortStack(s));
        }

    }
    return result;

}
//task4
void mostOccurencesInWords(string s){
 map<string, int> m;
 string current;
 //razdelqne na dymi
     for(int i=0; s[i]!='\0'; i++){

        if(s[i]==' ' || s[i]=='\n' || s[i]=='\t' || s[i]==',' ||s[i]=='.' || s[i]=='!' ){
            if(m.count(current)>0){ //ako veche go ima
               // m->value+=1; //value my se yvelichava
                m[current]+=1;

            }
            m[current]=1;
	// where does current change

        }
        else{
            current+=s[i];
        }


     }

    vector<string> arr;
    for(int i = 0; i<10; i++){
    int maxC;
    string maxWord;
       for(map<string, int>::iterator it = m.begin(); it != m.end(); it++){
        maxC = 0;
        maxWord = "";

        if(it->second > maxC){
            maxWord = it->first;
            maxC = it->second; //m.count(*it->first);
        }

       }
       arr.push_back(maxWord);
       m.erase(m.find(maxWord));

    }
    for(int i=0; i<arr.size(); i++){
        for(int j=0; j<arr[i].size(); j++){
            cout<<arr[j];
        }
        cout<<" ";
    }
    cout<<endl;


}

int main()
{
    //task1
    Node a1(9);
    Node b1(10, &a1);
    Node c1(15, &b1);

    Node a2(10);
    Node b2(6, &a2);
    Node c2(8, &b2);

    intersect(&c1, &c2);
    union1(&c1, &c2);

    //task2
    NodeT t1(3);
    NodeT t2(6);
    NodeT t3(5, &t1, &t2);
    NodeT t4(11);
    NodeT t5(14);
    NodeT t6(15, &t4, &t5);
    NodeT t7 (10, &t3, &t6);

    fixMistake(&t7);

    stack<int> s;
    s.push(2);
    s.push(1);
    s.push(3);
    stack<int> result = sortStack(s);


    //v str e zapisan celiqt string ot faila
    string str = "The most interesting subject in Computer sciences is programming. Many people like programming.";
    mostOccurencesInWords(str);



    return 0;
}
