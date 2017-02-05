#include <iostream>
#include <stack>
#include <string>
#include <cmath>
using namespace std;

stack<char> operations;
stack<double> numbers;

string input;

void print(stack<double> &s)
{
	if (s.empty())
	{
		return;
	}
	double x = s.top();
	s.pop();
	print(s);
	s.push(x);
	cout << x << " ";
}

int getSize(string input)
{
	int num = 0;
	while (input[num] != '\0')
	{
		num++;
	}
	return num;
}

int getPrecedence(char op)
{
	if (op == '+' ||op=='-')
	{
		return 1;
	}
	
	else if (op == '*' || op == '/')
	{
		return 2;
	}
	else if (op == '^')
	{
		return 3;
	}
	else if (op == 'l' || op == 'r' || op == 's' || op == 'c' || op == '_')
	{
		return 4;
	}
}

double calculate(string input)
{
	double val = 0;
	int size = getSize(input);
	int n = 1;
	for (int i = 0; i<size; i++)
	{

		if (input[i] >= '0'&&input[i] <= '9')
		{
			val = val * 10 + input[i] - 48;
		}
		else if (input[i] == '.')
		{
			while (input[i++] >= '0'&&input[i++] <= '9')
			{
				val = val + ((input[i] - 48) / pow(10, n));
				n++;
				i++;
			}
		}
		else
		{
			if (operations.empty())
			{
				numbers.push(val);
				operations.push(input[i]);
			}
			else if (getPrecedence(operations.top()) <= getPrecedence(input[i]))
			{
				numbers.push(val);
				operations.push(input[i]);
			}
			else
			{
				double num1 = numbers.top();
				numbers.pop();
				double num2 = val;

				if (operations.top() == '+')
				{
					numbers.push(num1 + num2);
				}
				else if (operations.top() == '_')
				{
					numbers.push(num2*(-1));
				}
				else if (operations.top() == '-')
				{
					numbers.push(num1 - num2);
				}
				else if (operations.top() == '*')
				{
					numbers.push(num1 * num2);
				}
				else if (operations.top() == '/')
				{
					if (num2 == 0)
					{
						cout << "Division by 0!" << endl;
					}
					else
					{
						numbers.push(num1 / num2);
					}
				}
				else if (operations.top() == '^')
				{
					numbers.push(pow(num1, num2));
				}
				else if (operations.top() == 'r')
				{
					numbers.push(sqrt(num2));
				}
				else if (operations.top() == 'l')
				{
					numbers.push(log(num2));
				}
				else if (operations.top() == 's')
				{
					numbers.push(sin(num2*3.14 / 180));
				}
				else if (operations.top() == 'c')
				{
					numbers.push(cos(num2*3.14 / 180));
				}
				operations.pop();
				operations.push(input[i]);
			}
			val = 0;
		}

	}

	numbers.push(val);

	while (!operations.empty())
	{
		double num2 = numbers.top();
		numbers.pop();
		double num1 = numbers.top();
		numbers.pop();

		if (operations.top() == '+')
		{
			numbers.push(num1 + num2);
		}
		else if (operations.top() == '_')
		{
			numbers.push(num2*(-1));
		}
		else if (operations.top() == '-')
		{
			numbers.push(num1 - num2);
		}
		else if (operations.top() == '*')
		{
			numbers.push(num1 * num2);
		}
		else if (operations.top() == '/')
		{
			if (num2 == 0)
			{
				cout << "Division by 0!" << endl;
				break;
			}
			else
			{
				numbers.push(num1 / num2);
			}
		}
		else if (operations.top() == '^')
		{
			numbers.push(pow(num1, num2));
		}
		else if (operations.top() == 'r')
		{
			numbers.push(sqrt(num2));
		}
		else if (operations.top() == 'l')
		{
			numbers.push(log(num2));
		}
		else if (operations.top() == 's')
		{
			numbers.push(sin(num2*3.14 / 180));
		}
		else if (operations.top() == 'c')
		{
			numbers.push(cos(num2*3.14 / 180));
		}
		operations.pop();
	}
	return numbers.top();
}

int main()
{
	string again;
	cout << "Welcome to my crippled calculator" << endl;
	cout << "You can choose between these operations: + , - , * , / ." << endl;
	cout << "To use a negative number: if your number is 'a', write: '_a' ." << endl;
	cout << "To use the exponent of a number, write '^' ." << endl;
	cout << "For the sin of a number, write 's' ." << endl;
	cout << "For the cos of a number, write 'c' ." << endl;
	cout << "For the log of a number, write 'l' ." << endl;
	cout << "Enter an expression: " << endl;

	cin >> input;
	cout << "Result: " << calculate(input) << endl;
	cout << "If you need help, write 'help'." << endl;
	cout << "If you want to see all results until now, write 'show'." << endl;
	cout << "If you want to run the program again, write 'again'" << endl;
	cout << "If you want to quit, write 'quit'" << endl;
	while (cin >> again)
	{
		if (again == "help")
		{
			cout << "Check the expression you've entered!" << endl;
		}
		if (again == "again")
		{
			main();
		}
		if (again == "quit")
		{
			exit(0);
		}
		if (again == "show")
		{
			print(numbers);
		}
	}
	return 0;
}
