#include <iostream>
#include<map>
#include<vector>
using namespace std;

struct Node
{
	int data;
	Node* left;
	Node* right;

	Node(int dat,Node*l,Node*r)
	{
	    data=dat;
	    left=l;
	    right=r;
	}
};
//Задача 1
int findMax (Node root)
{
    if(root.right!=NULL)
    {
        findMax(*root.right);
    }

    else
        return root.data;


}


int findMin (Node root)
{
    if(root.left!=NULL)
    {
        findMax(*root.left);
    }

    else
        return root.data;


}








//Задача 2


//функцията вкарава елементите от дървото във вектор
void helper(vector<int>&v,Node *tree)
{
    if(tree!=NULL)
    {

         v.push_back(tree->data);
    }
    if(tree->left!=NULL)
    {
        helper(v,tree->left);
    }

    if(tree->right!=NULL)
    {
        helper(v,tree->right);
    }
}

void PrintCommon (Node first,Node second)
{

    map <int,bool> myMap; //Ще я използваме за да опредемлим общите елементи

    vector<int>fir;//векторът ще съдържа елемнтите от първото дърво

    Node *poinToFirst=&first;// указател към първото дърво

    helper(fir,poinToFirst);

    for(int i:fir)
    {
        myMap[i]=true;
    }

    vector<int>sec;

    Node *pointToSecond=&second;

    helper(sec,pointToSecond);

    for(int j :sec)
    {
        if(myMap[j])
            cout<<j<<endl;

    }



}


//ЗАДАЧА 3
class TwoStacks

{
private:
    vector<int> twoStacks;


public:
    TwoStacks()
    {

    }

    void push1(int forFirst)

    {

        twoStacks.push_back(forFirst);

        twoStacks.push_back(100000001);//ще служи за граница


    }

    void push2(int forSecond)

    {

        twoStacks.push_back(forSecond);

        twoStacks.push_back(100000002);//ще служи за граница



    }

    void pop1()

    {

        vector<int> helper;
        int j=twoStacks.size();

        for(int i=j-1 ;i>0 ;i--)
        {

            if(twoStacks[i]==100000001)
            {

                twoStacks.pop_back();

                twoStacks.pop_back();

                break;
            }

            else
            {
                helper.push_back(twoStacks[i]);

                twoStacks.pop_back();


            }

        }


        //Сега ако има нужда запълваме векторът със стойностите от втория стек, които сме изхвърлили

        if(!helper.empty())
        {

     int j =helper.size();

            for(int i =j-1;i>=0;i--)
            {

                twoStacks.push_back(helper[i]);


            }


        }



    }



    void pop2()

    {

        vector<int> helper;
        int j=twoStacks.size();

        for(int i=j-1 ;i>=0 ;i--)
        {
            if(twoStacks[i]==100000002)
            {
                twoStacks.pop_back();

                twoStacks.pop_back();

                break;
            }

            else
            {
                helper.push_back(twoStacks[i]);


            }

        }


        //Сега ако има нужда запълваме векторът със стойностите от втория стек, които сме изхвърлили

        if(!helper.empty())
        {

            int j =helper.size();
            for(int i =j-1;i>=0;i--)
            {

                twoStacks.push_back(helper[i]);
                helper.pop_back();

            }


        }



    }

    void print()

    {
        for(int i=0;i<twoStacks.size();i++)
        {
            cout<<twoStacks[i]<<endl;

        }

    }






};






int main()
{


     Node c(111,NULL,NULL);

     Node b(12,&c,NULL);

     Node a(88,&b,&c);





     cout<<"testsForTask1"<<endl;

     cout<<findMax(a)<<endl;

     cout<<findMin(a)<<endl;





   cout<<"testsForTask2"<<endl;

          PrintCommon(a,b);





   cout<<"testsForTask3"<<endl;
TwoStacks test;
test.push1(111);
test.push1(999);
test.push2(9321);
test.push2(2193);
test.pop2();
test.print();



    return 0;
}
