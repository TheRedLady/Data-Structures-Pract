#include <iomanip>
#include <stack>
#include <cmath>
#include <string>
#include <iostream>
#include <assert.h>

using namespace std;

int convertToInt(string number)
{
    int result = 0;
    int exp = 1;
    for(int i = number.length()-1 ; i >= 0 ; i--)
    {
        result +=  ((int)number[i] - '0') * exp;
        exp *= 10;
    }
    return result;
}

double convertToDouble(string number)
{
    double result = 0;
    int exp = 1;
    int len = 1;
    bool flag = false;
    for(int i = 0 ; i < number.length() ; i++)
    {
        if(flag)
            len *= 10;

        if(number[i] == '.')
            flag = true;
    }

    for(int i = number.length() -1 ; i >= 0 ; i--)
    {
        if(number[i] != '.')
        {
            result += ((int)number[i] - '0') * exp;
            exp *= 10;
        }
    }

    return result/len;
}

void showStack(stack<string> current)
{
    while(!current.empty())
    {
        cout << "|     " << current.top() <<endl;

        current.pop();
    }
    cout << "********************************" <<endl;
}

stack<string> usingStack(string act)
{
    stack<string> operations;

    ///Slagame elementite ot string-a
    for(int i = 0 ; i < act.length() ; i++)
    {
        string temp = "";
        ///Puhane na funkcii
        if((act[i] == 's') || (act[i] == 'c') || (act[i] == 'l') || (act[i] == 'e'))
        {
            while(act[i] != ')')
            {
                temp.push_back(act[i]);
                i += 1;
            }
            temp.push_back(act[i]);
            operations.push(temp);
        }
        else
        {
            if((act[i] != '+' && act[i] != '-' && act[i] != '*' && act[i] != '/') && (i < act.length()))
            {
                while((act[i] != '+' && act[i] != '-' && act[i] != '*' && act[i] != '/') && (i < act.length()))
                {
                    temp.push_back(act[i]);
                    i += 1;
                }
                operations.push(temp);
            }


            if(i < act.length())
                {
                    temp = act[i];
                    operations.push(temp);
                }
        }


    }

    return operations;
}

///Podgotovka za rabota s operandite
stack<string> getReady(stack<string> operations)
{
    stack<string> result;
    while(!operations.empty())
    {
        result.push(operations.top());
        operations.pop();
    }
    return result;
}

stack<string> clearStack(stack<string> operations)
{
    while(!operations.empty())
        operations.pop();
    return operations;
}

stack<string> appendToStack(string act, stack<string> help)///!!!Da se OPRAVI SEGA
{
    stack<string> result;
    result = help;
    ///Nabutvame novite elementi
    for(int i = 0 ; i < act.length() ; i++)
    {
        string temp = "";

        if((act[i] == 's') || (act[i] == 'c') || (act[i] == 'l') || (act[i] == 'e'))
        {
            while(act[i] != ')')
            {
                temp.push_back(act[i]);
                i += 1;
            }
            temp.push_back(act[i]);
            result.push(temp);
        }
        else
        {
            if((act[i] != '+' && act[i] != '-' && act[i] != '*' && act[i] != '/') && (i < act.length()))
            {
                while((act[i] != '+' && act[i] != '-' && act[i] != '*' && act[i] != '/') && (i < act.length()))
                {
                    temp.push_back(act[i]);
                    i += 1;
                }
                result.push(temp);
            }


            if(i < act.length())
                {
                    temp = act[i];
                    result.push(temp);
                }
        }


    }

    return result;
}

stack<string> appendStacks(stack<string> all, stack<string> calc)
{
    stack<string> result;
    result = all;

    all = clearStack(all);

    ///Nabutvame novite elementi
    while(!calc.empty())
    {
        all.push(calc.top());
        calc.pop();
    }

    while(!all.empty())
    {
        result.push(all.top());
        all.pop();
    }
    cout << "Stana"<< endl;
    return result;
}

///CONVERTIRAME OT DOUBLE KUM STRING
///Priemam che do deset hilqdni shte razglejdam chislata
string convertToString(double number)
{
    string result = "";
    stack<char> base;
    stack<char> point;
    int base_int =(int)number;
    int floating;

    bool flag = false;
    if(base_int == 0)
    {
        base.push('0');
    }
    if(number < 0)
    {
        flag = true;
        base_int *= -1;
    }
    while(base_int != 0)
    {
        char symbol;
        symbol = (char)(base_int % 10 + '0');
        base.push(symbol);
        base_int /= 10;
    }
    if(flag)
    {
        base.push('-');
    }
    ///Pri otricatelni malko po-razlichno...
    if(!flag)
        floating = 10000*(number - (int)number);
    else
    {
        number = (-1) * number;
        floating = 10000*(number - (int)number);
    }


    if(floating == 0)
    {
        point.push('0');
    }
    while(floating != 0)
    {
        char symbol;
        if(flag)
        {
            symbol = (char)(floating % 10 + '0');
        }

        else
            symbol = (char)(floating % 10 + '0');

        point.push(symbol);
        floating /= 10;
    }
    while(!base.empty())
    {
        result.push_back(base.top());
        base.pop();
    }

    result.push_back('.');

    while(!point.empty())
    {
        result.push_back(point.top());
        point.pop();
    }

    return result;
}

///Arithmetic operations
double addition(double a, double b)
{
    return a + b;
}

double subtract(double a, double b)
{
    return a - b;
}

double multiplication(double a, double b)
{
    return a * b;
}

double division(double a, double b)
{
    return a / b;
}

///Standart functions
double sine(double argument)///(rad)
{
    return sin(argument);
}

double cosine(double argument)///(rad)
{
    return cos(argument);
}

double naturalLog(double argument)
{
    return log(argument);
}

double exponent(double argument)
{
    return exp(argument);
}

double squareRoot(double argument)
{
    return sqrt(argument);
}

///OT TUK *****************************************************************
string calculatingFunc(stack<string> operations)
{
    double result = 0;
    double a, b, c;
    stack<string> opers;
    stack<string> numbers;

    while(!operations.empty())
    {
        if(operations.top() == "+" || operations.top() == "-" || operations.top() == "*" || operations.top() == "/")
            opers.push(operations.top());
        else
        {
            numbers.push(operations.top());
        }

        operations.pop();
    }

    if((opers.empty()) && (!numbers.empty()))
    {
        result = convertToDouble(numbers.top());
        numbers.pop();
        return convertToString(result);
    }

    if(((opers.top() == "+") || (opers.top() == "-")) && (opers.size() == numbers.size()))
    {
        string save = opers.top();
        opers.pop();
        if(opers.empty())
        {
            if(save == "+")
                result += convertToDouble(numbers.top());
            else
                result -= convertToDouble(numbers.top());

            return convertToString(result);
        }

        if((opers.top() != "*") && (opers.top() != "/"))
        {
            if(save == "+")
            {
                    result += convertToDouble(numbers.top());
            }
            else
            {
                    result -= convertToDouble(numbers.top());
            }
            numbers.pop();
        }
        else
        {
            opers.push(save);
        }

    }

    if(opers.size() != numbers.size())
    {
        if((opers.top() == "+") ||(opers.top() == "-"))
        {
                result += convertToDouble(numbers.top());
                numbers.pop();
        }
    }

    while(!opers.empty())
    {
        string symbol = opers.top();
        string symbol1;
        string symbol2;
        string symbol3;
        string symbol4;
        opers.pop();
        c = 0;

        if((symbol == "+") && (opers.empty()) && (!numbers.empty()))
        {
            a = convertToDouble(numbers.top());
            numbers.pop();

            if(!numbers.empty())
            {
                b = convertToDouble(numbers.top());
                numbers.pop();

                result += addition(a, b);
            }
            else
                result += a;
        }

        if((symbol == "-") && (opers.empty()) && (!numbers.empty()))///Opraveno
        {
            a = convertToDouble(numbers.top());
            numbers.pop();


            if(!numbers.empty())
            {
                b = convertToDouble(numbers.top());
                numbers.pop();

                result += subtract(a, b);
            }
            else
                result -= a;
        }

        if(((symbol == "*") || (symbol == "/")) && (opers.empty()) && (!numbers.empty()))
        {
            a = convertToDouble(numbers.top());
            numbers.pop();

            b = convertToDouble(numbers.top());
            numbers.pop();

            if(symbol == "*")
                result += multiplication(a, b);
            else
                result += division(a, b);
        }


        ///ZA PLUS !!!!
        if((symbol == "+") && (!opers.empty()) && (!numbers.empty())) /// RABOTI ZA +,*.../...+;
        {
            if((opers.top() == "*") || (opers.top() == "/"))
            {
                symbol2 = opers.top();
                opers.pop();

                a = convertToDouble(numbers.top());
                numbers.pop();

                b = convertToDouble(numbers.top());
                numbers.pop();

                if(symbol2 == "*")
                    c += multiplication(a, b);
                else
                    c += division(a, b);

                while(!opers.empty())
                {
                    symbol1 = opers.top();
                    if(symbol1 != "-" && symbol1 != "+")
                    {
                        opers.pop();
                        if(symbol1 == "*" || symbol1 == "/")
                        {
                            a = convertToDouble(numbers.top());
                            numbers.pop();

                            if(symbol1 == "*")
                                c *= a;
                            else
                                c /= a;
                        }
                    }
                    else
                    {
                        break;
                    }

                }

                result += c;
                c = 0;
            }
            else
            {
                if(opers.top() == "+")
                {
                    symbol = opers.top();///+
                    opers.pop();///symbol helper

                    a = convertToDouble(numbers.top());
                    numbers.pop();

                    if(!opers.empty())
                    {
                        if(opers.top() != "*" && opers.top() != "/")///VAJNO!!
                        {
                            b = convertToDouble(numbers.top());
                            numbers.pop();

                            result += addition(a, b);
                        }
                        else
                        {
                            opers.push(symbol);
                            result += a;
                        }
                    }
                    else
                    {
                        opers.push(symbol);
                        result += a;
                    }
                }
                else if(opers.top() == "-")
                {
                    a = convertToDouble(numbers.top());
                    numbers.pop();

                    result += a;
                }

            }
        }

        ///ZA MINUS!!!
        if((symbol == "-") && (!opers.empty()) && (!numbers.empty())) /// RABOTI ZA -,*.../...-;
        {
            if((opers.top() == "*") || (opers.top() == "/"))
            {
                symbol3 = opers.top();
                opers.pop();

                a = convertToDouble(numbers.top());
                numbers.pop();

                b = convertToDouble(numbers.top());
                numbers.pop();

                if(symbol3 == "*")
                    c -= multiplication(a, b);
                else
                    c -= division(a, b);

                while(!opers.empty())
                {
                    symbol1 = opers.top();
                    if(symbol1 != "-" && symbol1 != "+")
                    {
                        opers.pop();
                        if(symbol1 == "*" || symbol1 == "/")
                        {
                            a = convertToDouble(numbers.top());
                            numbers.pop();

                            if(symbol1 == "*")
                                c *= a;
                            else
                                c /= a;
                        }
                    }
                    else
                    {
                        break;
                    }

                }
                result += c;
                c = 0;
            }
            else
            {
                if(opers.top() == "-")
                {
                    symbol = opers.top();
                    opers.pop();

                    a = convertToDouble(numbers.top());
                    numbers.pop();

                    if(!opers.empty())
                    {
                        if(opers.top() != "*" && opers.top() != "/")
                        {

                        b = convertToDouble(numbers.top());
                        numbers.pop();

                        result -= addition(a, b);
                        }
                        else///Velik vissh pilotaj
                        {
                            opers.push(symbol);
                            result -= a;
                        }
                    }
                    else
                    {
                        opers.push(symbol);
                        result -= a;
                    }


                }
                else if(opers.top() == "+")
                {
                    a = convertToDouble(numbers.top());
                    numbers.pop();

                    result -= a;
                }
            }

        }

        ///ZA UMNOJENIE I DELENIE
        if(((symbol == "*") || (symbol == "/")) && (!numbers.empty()) && (!opers.empty()))
        {
                a = convertToDouble(numbers.top());
                numbers.pop();

                b = convertToDouble(numbers.top());
                numbers.pop();

                ///NOTE: DA SE OPRAVI ZA POVTORENIQ
                if(symbol == "*")
                    c += multiplication(a, b);
                else
                    c += division(a, b);

                if((opers.top() == "*") || (opers.top() == "/"))
                {
                    while(!opers.empty())
                    {
                        symbol = opers.top();
                        if((symbol != "+") && (symbol != "-"))
                        {
                            opers.pop();

                            a = convertToDouble(numbers.top());
                            numbers.pop();

                            if(symbol == "*")
                                c *= a;
                            else
                                c /= a;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                result += c;
                c = 0;
        }
    }

    return convertToString(result);
}
///DO TUK **********************************************************


double functionCalculator(string func)
{
    if(func.substr(0,3) == "sin")
    {
        string argument;
        int i = 4;
        while(func[i] != ')')
        {
            argument.push_back(func[i]);
            i += 1;
        }
        return sine(convertToDouble(calculatingFunc(usingStack(argument))));///Lele
    }

    if(func.substr(0,3) == "cos")
    {
        string argument;
        int i = 4;
        while(func[i] != ')')
        {
            argument.push_back(func[i]);
            i += 1;
        }
        return cosine(convertToDouble(calculatingFunc(usingStack(argument))));
    }

    if(func.substr(0,3) == "log")
    {
        string argument;
        int i = 4;
        while(func[i] != ')')
        {
            argument.push_back(func[i]);
            i += 1;
        }
        return naturalLog(convertToDouble(calculatingFunc(usingStack(argument))));
    }

    if(func.substr(0,3) == "exp")
    {
        string argument;
        int i = 4;
        while(func[i] != ')')
        {
            argument.push_back(func[i]);
            i += 1;
        }
        return exponent(convertToDouble(calculatingFunc(usingStack(argument))));
    }

    if(func.substr(0,4) == "sqrt")
    {
        string argument;
        int i = 5;
        while(func[i] != ')')
        {
            argument.push_back(func[i]);
            i += 1;
        }
        return squareRoot(convertToDouble(calculatingFunc(usingStack(argument))));
    }

}

///WITHOUT STANDART FUNCTIONS IN ONE ANOTHER


string calculating(stack<string> operations)
{
    double result = 0;
    double a, b, c;
    stack<string> opers;
    stack<string> numbers;

    while(!operations.empty())
    {
        if(operations.top() == "+" || operations.top() == "-" || operations.top() == "*" || operations.top() == "/")
            opers.push(operations.top());
        else
        {
            numbers.push(operations.top());
        }

        operations.pop();
    }

    if((opers.empty()) && (!numbers.empty()))
    {

            if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                result = functionCalculator(numbers.top());
            else
                result = convertToDouble(numbers.top());
        numbers.pop();
        return convertToString(result);
    }


    if(((opers.top() == "+") || (opers.top() == "-")) && (opers.size() == numbers.size()))
    {
        string save = opers.top();
        opers.pop();

        if(opers.empty())
        {
            if(save == "+")
            {
                if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                    result += functionCalculator(numbers.top());
                else
                    result += convertToDouble(numbers.top());
            }

            else
            {
                if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                    result = functionCalculator(numbers.top());
                else
                    result -= convertToDouble(numbers.top());
            }

            return convertToString(result);
        }

        if((opers.top() != "*") && (opers.top() != "/"))
        {
            if(save == "+")
            {
                if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                    result += functionCalculator(numbers.top());
                else
                    result += convertToDouble(numbers.top());
            }
            else
            {
                if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                    result -= functionCalculator(numbers.top());
                else
                    result -= convertToDouble(numbers.top());
            }
            numbers.pop();
        }
        else
        {
            opers.push(save);
        }

    }

    if(opers.size() != numbers.size())
    {
        if((opers.top() == "+") ||(opers.top() == "-"))
        {
            if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                result += functionCalculator(numbers.top());
            else
                result += convertToDouble(numbers.top());

                numbers.pop();
        }
    }

    while(!opers.empty())
    {
        string symbol = opers.top();
        string symbol1;
        string symbol2;
        string symbol3;
        string symbol4;
        opers.pop();
        c = 0;

        if((symbol == "+") && (opers.empty()) && (!numbers.empty()))
        {
            if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                a = functionCalculator(numbers.top());
            else
                a = convertToDouble(numbers.top());

            numbers.pop();
            if(!numbers.empty())
            {
                if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                    b = functionCalculator(numbers.top());
                else
                    b = convertToDouble(numbers.top());
                numbers.pop();
                result += addition(a, b);
            }
            else
                result += a;
        }

        if((symbol == "-") && (opers.empty()) && (!numbers.empty()))///Opraveno
        {
            if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                a = functionCalculator(numbers.top());
            else
                a = convertToDouble(numbers.top());
            numbers.pop();
            if(!numbers.empty())
            {
                if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                    b = functionCalculator(numbers.top());
                else
                    b = convertToDouble(numbers.top());
                numbers.pop();
                result += subtract(a, b);
            }
            else
                result -= a;
        }

        if(((symbol == "*") || (symbol == "/")) && (opers.empty()) && (!numbers.empty()))
        {
            if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                a = functionCalculator(numbers.top());
            else
                a = convertToDouble(numbers.top());
            numbers.pop();

            if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                b = functionCalculator(numbers.top());
            else
                b = convertToDouble(numbers.top());
            numbers.pop();

            if(symbol == "*")
                result += multiplication(a, b);
            else
                result += division(a, b);
        }


        ///ZA PLUS !!!!
        if((symbol == "+") && (!opers.empty()) && (!numbers.empty())) /// RABOTI ZA +,*.../...+;
        {
            if((opers.top() == "*") || (opers.top() == "/"))
            {
                symbol2 = opers.top();
                opers.pop();

                if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                    a = functionCalculator(numbers.top());
                else
                    a = convertToDouble(numbers.top());
                numbers.pop();

                if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                    b = functionCalculator(numbers.top());
                else
                    b = convertToDouble(numbers.top());
                numbers.pop();

                if(symbol2 == "*")
                    c += multiplication(a, b);
                else
                    c += division(a, b);

                while(!opers.empty())
                {
                    symbol1 = opers.top();
                    if(symbol1 != "-" && symbol1 != "+")
                    {
                        opers.pop();
                        if(symbol1 == "*" || symbol1 == "/")
                        {
                            if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                                a = functionCalculator(numbers.top());
                            else
                                a = convertToDouble(numbers.top());
                            numbers.pop();

                            if(symbol1 == "*")
                                c *= a;
                            else
                                c /= a;
                        }
                    }
                    else
                    {
                        break;
                    }

                }

                result += c;
                c = 0;
            }
            else
            {
                if(opers.top() == "+")
                {
                    symbol = opers.top();///+
                    opers.pop();///symbol helper
                    if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                        a = functionCalculator(numbers.top());
                    else
                        a = convertToDouble(numbers.top());
                    numbers.pop();

                    if(!opers.empty())
                    {
                        if(opers.top() != "*" && opers.top() != "/")///VAJNO!!
                        {
                            if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                                b = functionCalculator(numbers.top());
                            else
                                b = convertToDouble(numbers.top());
                            numbers.pop();

                            result += addition(a, b);
                        }
                        else
                        {
                            opers.push(symbol);
                            result += a;
                        }
                    }
                    else
                    {
                        opers.push(symbol);
                        result += a;
                    }
                }
                else if(opers.top() == "-")
                {
                    if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                        a = functionCalculator(numbers.top());
                    else
                        a = convertToDouble(numbers.top());
                    numbers.pop();

                    result += a;
                }

            }
        }

        ///ZA MINUS!!!
        if((symbol == "-") && (!opers.empty()) && (!numbers.empty())) /// RABOTI ZA -,*.../...-;
        {
            if((opers.top() == "*") || (opers.top() == "/"))
            {
                symbol3 = opers.top();
                opers.pop();

                if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                    a = functionCalculator(numbers.top());
                else
                    a = convertToDouble(numbers.top());
                numbers.pop();

                if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                    b = functionCalculator(numbers.top());
                else
                    b = convertToDouble(numbers.top());
                numbers.pop();

                if(symbol3 == "*")
                    c -= multiplication(a, b);
                else
                    c -= division(a, b);

                while(!opers.empty())
                {
                    symbol1 = opers.top();
                    if(symbol1 != "-" && symbol1 != "+")
                    {
                        opers.pop();
                        if(symbol1 == "*" || symbol1 == "/")
                        {
                            if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                                a = functionCalculator(numbers.top());
                            else
                                a = convertToDouble(numbers.top());
                            numbers.pop();

                            if(symbol1 == "*")
                                c *= a;
                            else
                                c /= a;
                        }
                    }
                    else
                    {
                        break;
                    }

                }
                result += c;
                c = 0;
            }
            else
            {
                if(opers.top() == "-")
                {
                    symbol = opers.top();
                    opers.pop();
                    if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                        a = functionCalculator(numbers.top());
                    else
                        a = convertToDouble(numbers.top());
                    numbers.pop();

                    if(!opers.empty())
                    {
                        if(opers.top() != "*" && opers.top() != "/")
                        {

                        if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                            b = functionCalculator(numbers.top());
                        else
                            b = convertToDouble(numbers.top());
                        numbers.pop();

                        result -= addition(a, b);
                        }
                        else///Velik vissh pilotaj
                        {
                            opers.push(symbol);
                            result -= a;
                        }
                    }
                    else
                    {
                        opers.push(symbol);
                        result -= a;
                    }


                }
                else if(opers.top() == "+")
                {
                    if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                        a = functionCalculator(numbers.top());
                    else
                        a = convertToDouble(numbers.top());
                    numbers.pop();

                    result -= a;
                }
            }

        }

        ///ZA UMNOJENIE I DELENIE
        if(((symbol == "*") || (symbol == "/")) && (!numbers.empty()) && (!opers.empty()))
        {
                if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                    a = functionCalculator(numbers.top());
                else
                    a = convertToDouble(numbers.top());
                numbers.pop();

                if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                    b = functionCalculator(numbers.top());
                else
                    b = convertToDouble(numbers.top());
                numbers.pop();

                ///NOTE: DA SE OPRAVI ZA POVTORENIQ
                if(symbol == "*")
                    c += multiplication(a, b);
                else
                    c += division(a, b);

                if((opers.top() == "*") || (opers.top() == "/"))
                {
                    while(!opers.empty())
                    {
                        symbol = opers.top();
                        if((symbol != "+") && (symbol != "-"))
                        {
                            opers.pop();
                            if((numbers.top().substr(0,3) == "sin") || (numbers.top().substr(0,3) == "cos") || (numbers.top().substr(0,3) == "log") || (numbers.top().substr(0,3) == "exp") || (numbers.top().substr(0,4) == "sqrt"))
                                a = functionCalculator(numbers.top());
                            else
                                a = convertToDouble(numbers.top());
                            numbers.pop();

                            if(symbol == "*")
                                c *= a;
                            else
                                c /= a;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                result += c;
                c = 0;
        }
    }

    return convertToString(result);
}


void helpInstructions()
    {
        cout << "-----Help-----" << endl;
        cout << "clear -> delete stack" << endl;
        cout << "pop -> delete top of the stack" << endl;
        cout << "show -> show current stack" << endl;
        cout << "= -> look at top of stack (result)" <<endl;
        cout << "quit -> exit calculator" << endl;
        cout << "---Arithmetic operations---" << endl;
        cout << "+ = addition" << endl;
        cout << "- = subtract" << endl;
        cout << "* = multiplication" << endl;
        cout << "/ = partition" << endl;
        cout << "---Standart functions---" << endl;
        cout << "sin(x) = sine function" << endl;
        cout << "cos(x) = cosine function" << endl;
        cout << "exp(x) = e^x" << endl;
        cout << "log(x) = ln(x)" << endl;
        cout << "sqrt(x) = x^(1/2)" << endl;
    }


int main()
{
    string action;
    stack<string> calculate;
    stack<string> all_actions;
    ///Startirane
    cout << "-----------------Calculator-----------------" << endl;
    cin >> action;
    while(action != "quit")
    {
        if((action == "clear") && (!calculate.empty()))
        {
            calculate = clearStack(calculate);
            all_actions = clearStack(all_actions);
        }

        if((action == "pop") && (!calculate.empty()))
        {
            cout << "WARNING!" << endl;
            ///Za obshtiq stek
            all_actions.pop();
        }

        if(action == "show")
            showStack(all_actions);

        if(action == "help")
            helpInstructions();

        if(action == "=")///pri izpolzvane se zapisva resultatut na vurha i se izvejda (II variant)
        {
            if(!all_actions.empty())
                cout << all_actions.top() <<endl;
            else
                cout << 0 <<endl;
        }


        if(action != "quit" && action != "clear" && action != "show" && action != "help" && action != "=")
        {
            if(!calculate.empty())
            {
                stack<string> helper = calculate;
                calculate = appendToStack(action, helper);
            }
            else
                calculate = usingStack(action);

            ///Izchislqvane i zapisvane na vsichki operandi s rezultat
            all_actions = appendToStack(action, all_actions);
            all_actions.push(calculating(calculate));
        }

        cin >> action;
    }

    return 0;
}

