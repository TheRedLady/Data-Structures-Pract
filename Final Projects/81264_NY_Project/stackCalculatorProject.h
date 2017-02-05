#include <iostream>
#include <stack>
#include <vector>
#include <sstream>
#include <cmath>
#include <string>
#include <stdlib.h>

using namespace std;

class StackCalculator
{
private:
	vector<string> tokens;
	vector<string> outputList;
	stack<string> toPostfix;
	stack<float> resultStack;
	stack<string> functions;
public:
	bool isOperand(const string& symbol);
	bool isOperator(const string& c);
	bool isFunction(const string& element);
	int checkPriority(const string& c);
	float stringToInt(string c);
	float mypow(float base, float exp);
	float numberOfDigits(float n);
	float decimalPointNumber(float num1,float num2);
	float squareRoot(float num);
	float naturalLogarithm(float num);
	float sinExecute(float num);
	float cosExecute(float num);
	float makeNegative(float num);
	vector<string> inputToPostfix(string input);
	float calculate(vector<string> expression);
    void show();
    void help();
    void quit();
};


bool StackCalculator::isOperand(const string& symbol)
{
	 if(!isdigit(symbol[0]))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool StackCalculator::isOperator(const string& c)
{
	return (c == "+" || c == "-" || c == "*" || c == "/" || c == "^");
}

bool StackCalculator::isFunction(const string& element)
{
	return (element == "s" || element == "c" || element == "l" || element == "r" || element == "n" || element == ".");
}

int StackCalculator::checkPriority(const string& c)
{
	if(c == "^")
    {
        return 3;
    }

    if(c == "*" || c == "/")
    {
        return 2;
    }

    if(c== "+" || c == "-")
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

float StackCalculator::stringToInt(string elem)
{
    float value = 0;
    float i = 0;

    while(i < elem.size())
    {
        value *= 10;
        value += (int)(elem[i] - 48);
        i++;
    }
    return value;
}

float StackCalculator::mypow(float base, float exp)
{
	return exp == 0 ? 1 : base*mypow(base, exp - 1);
}

float StackCalculator::numberOfDigits(float n)
{
	float length = 0;

    while (n >= 1)
    {
        n /= 10;
        length += 1;
    }

    return length;
}

float StackCalculator::decimalPointNumber(float num1,float num2)
{
	float length = numberOfDigits(num1);
    float rem= mypow(10, length);

    num1 /= rem;

    float result;

    if (num2 >= 0)
    {
        result = num2 + num1;
    }

    else if (num2 < 0)
    {
        result = num2 - num1;
    }

    return result;
}

float StackCalculator::squareRoot(float num)
{
	return sqrt(num);
}

float StackCalculator::naturalLogarithm(float num)
{
	return log(num);
}

float StackCalculator::sinExecute(float num)
{
	return sin(num);
}

float StackCalculator::cosExecute(float num)
{
	return cos(num);
}

float StackCalculator::makeNegative(float num)
{
	return (0 - num);
}

vector<string> StackCalculator::inputToPostfix(string input)
{
	istringstream iss(input);
    while(iss)
    {
        string temp;
        iss >>temp;
        tokens.push_back(temp);
    }

    for(unsigned int i = 0; i < tokens.size(); i++)
    {
        if(isFunction(tokens[i]))
        {
            outputList.push_back(tokens[i]);
        }

        if(isOperand(tokens[i]))
        {
            outputList.push_back(tokens[i]);
        }

        if(tokens[i] == "(")
        {
            toPostfix.push(tokens[i]);
        }

        if(tokens[i] == ")")
        {
            while(!toPostfix.empty() && toPostfix.top() != "(")
            {
                outputList.push_back(toPostfix.top());
                toPostfix.pop();
            }
            toPostfix.pop();
        }

        if(isOperator(tokens[i]))
        {
            while(!toPostfix.empty() && checkPriority(toPostfix.top()) >= checkPriority(tokens[i]))
            {
                outputList.push_back(toPostfix.top());
                toPostfix.pop();
            }
            toPostfix.push(tokens[i]);
        }
    }

    //pop any remaining operators from the stack and insert to outputlist
    while(!toPostfix.empty())
    {
        outputList.push_back(toPostfix.top());
        toPostfix.pop();
    }

    cout<<endl;
    return outputList;
}

float StackCalculator::calculate(vector<string> expression)
{

    float result;
    float global;

    for(int i = 0; i < expression.size(); ++i)
    {
        int j = i;

        if(expression[i] == "!")
        {
            continue;
        }

        if(isOperand(expression[i]))
        {
            float c = stringToInt(expression[i]);
            resultStack.push(c);
        }

        if(isFunction(expression[i]))
        {
            while(isFunction(expression[j]))
            {
                functions.push(expression[j]);
                expression[j] = "!";
                j++;
            }

            float temp = stringToInt(expression[j]);
            float argument = temp;
            expression[j] = "!";

            while(!functions.empty())
            {
                string x = functions.top();

                if (x == "r")
                {
                    result = squareRoot(argument);

                }

                if (x == "l")
                {
                    result = naturalLogarithm(argument);

                }

                if (x == "s")
                {
                    result = sinExecute(argument);
                }

                if (x == "c")
                {
                    result = cosExecute(argument);
                }

                if (x == "n")
                {
                    result = makeNegative(argument);
                }

                if(x == "." )
                {
                    global = resultStack.top();
                    resultStack.pop();
                    result = decimalPointNumber(argument,global);
                }

                argument = result;
                functions.pop();
            }
            resultStack.push(argument);
        }

        if(expression[i] == "+")
        {
            float x = resultStack.top();
            resultStack.pop();

            float y = resultStack.top();
            resultStack.pop();

            result = x + y;
            resultStack.push(result);
        }

        if(expression[i] == "-")
        {
            float x = resultStack.top();
            resultStack.pop();

            float y = resultStack.top();
            resultStack.pop();

            result = y - x;
            resultStack.push(result);
        }

        if(expression[i] == "*")
        {
            float x = resultStack.top();
            resultStack.pop();

            float y = resultStack.top();
            resultStack.pop();

            result = x * y;
            resultStack.push(result);
        }

        if(expression[i] == "/")
        {
            float x = resultStack.top();
            resultStack.pop();

            float y = resultStack.top();
            resultStack.pop();

            result = y / x;
            resultStack.push(result);
        }

        if(expression[i] == "^")
        {
            float x = resultStack.top();
            resultStack.pop();

            float y = resultStack.top();
            resultStack.pop();

            result = mypow(y,x);
            resultStack.push(result);
        }
    }
    return resultStack.top();
}

void StackCalculator::show()
{
    for(unsigned int i = 0; i < outputList.size(); i++)
    {
        cout<<outputList[i];
    }
}

void StackCalculator::help()
{
    cout<<"Check your syntax again :)"<<endl;
}

void StackCalculator::quit()
{
    exit(0);
}
