#include <iostream>
#include "stackCalculatorProject.h"

using namespace std;

int main()
{

    cout<<"Welcome to my calculator."<<endl;
    cout<<endl;

    cout<<"This calculator supports the operations +,-,*,/,^"<<endl;
    cout<<endl;

    cout<<"If you want to use functions write: s for sin,c for cos,l for log,r for square root,n for negative number and . for decimal point number"<<endl;
    cout<<endl;

    cout<<"It is necessary to leave a space between each symbol."<<endl;
    cout<<endl;

    cout<<"There may be some inaccuracy in the answer but after all this is not NASA."<<endl;
    cout<<endl;

    StackCalculator calc;

    string input;
    vector<string> res;
    float finalRes;

    cout<<"Enter expression: "<<endl;
    getline(cin, input);

    res = calc.inputToPostfix(input);
    finalRes = calc.calculate(res);

    cout<<"Final result being: "<<finalRes<<endl;

    cout<<endl;

    string more;

    cout<<"If you need help,write 'help'"<<endl;
    cout<<"If you want to quit,write 'quit'"<<endl;
    cout<<"If you want to see the current progress,write 'show'"<<endl;

    while (cin >> more)
     {

        if (more == "show")
        {
            calc.show();
        }

        if (more == "help")
        {
           calc.help();
        }

        if (more == "quit")
        {
            calc.quit();
        }
    }
}

