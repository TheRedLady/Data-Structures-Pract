#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

struct DoubleStack
{
    private:
        vector <int> stacks;
        size_t numberOfElementsInFirstStack;
        size_t numberOfElementsInSecondStack;

    public:
        DoubleStack(): numberOfElementsInFirstStack(0), numberOfElementsInSecondStack(0) {}

        void push1(int x) /// O(stacks.size())
        {
            ++numberOfElementsInFirstStack;
            stacks.insert(stacks.begin(), x);
        }

        void push2(int x) /// O(1)
        {
            ++numberOfElementsInSecondStack;
            stacks.push_back(x);
        }

        int pop1() /// O(stacks.size())
        {
            assert(numberOfElementsInFirstStack);
            --numberOfElementsInFirstStack;
            int ret = stacks[0];
            stacks.erase(stacks.begin());
            return ret;
        }

        int pop2() /// O(1)
        {
            assert(numberOfElementsInSecondStack);
            --numberOfElementsInSecondStack;
            int ret = stacks.back();
            stacks.pop_back();
            return ret;
        }
};

void testDoubleStack()
{
    DoubleStack ds;
    //ds.pop1();
    //ds.pop2();
    ds.push1(5);
    ds.push2(-3);
    ds.push1(16);
    ds.push1(-35);
    ds.push2(23);
    ds.push2(0);
    ds.push2(5);
    ds.push1(-69);
    ds.push2(31);
    for (int i = 0; i < 4; i++)
        cout << ds.pop1() << endl;
    cout << endl;
    for (int i = 0; i < 5; i++)
        cout << ds.pop2() << endl;
    //ds.pop1();
    //ds.pop2();
}

int main()
{
    testDoubleStack();
    return 0;
}
