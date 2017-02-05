#include <iostream>
#include <string.h>
#include <math.h>
#include <string>
#include <stack>
#include <assert.h>

using namespace std;

#define PI 3.14159265

bool isNumber(char&a)
{
	if (!isdigit(a))
	{
		return false;
	}
	else
		return true;
}
bool IsOperand(char ch)
{
	if (ch >= '0' && ch <= '9')
	{
		return true;
	}
	return false;
}
bool IsOperator(char C)
{
	if (C == '+' || C == '-' || C == '*' || C == '/' || C == '^' || C == '.') {
		return true;
	}
	return false;
}
bool IsFunction(char C)
{
	if (C == 'r' || C == 's' || C == 'c' || C == 'l' || C == 'n') {
		return true;
	}
	return false;
}

bool IsLeftParenthesis(char ch)
{
	if (ch == '(') {
		return true;
	}
	return false;
}

bool IsRightParenthesis(char ch)
{
	if (ch == ')') {
		return true;
	}
	return false;
}
bool Flag(char ch)
{
	if (!IsOperand(ch) || !IsOperator(ch) || !IsLeftParenthesis(ch) || !IsRightParenthesis(ch)) {
		return false;
	}
	return true;
}

bool IsRightAssociative(char op)
{
	if (op == '^') {
		return true;
	}
	return false;
}
int GetOperatorWeight(char op)
{
	int weight = -1;
	switch (op) {
	case '+':
	case '-':
		weight = 1;
		break;
	case '*':
	case '/':
		weight = 2;
		break;
	case '^':
		weight = 3;
		break;
	case 'r':
	case 's':
	case 'c':
	case 'l':
	case 'n':
	case '.':
		weight = 4;
		break;
	}
	return weight;
}
bool HasHigherPrecedence(char op1, char op2)
{
	int op1Weight = GetOperatorWeight(op1);
	int op2Weight = GetOperatorWeight(op2);

	if (op1Weight == op2Weight) {
		if (IsRightAssociative(op1)) {
			return false;
		}
		else {
			return true;
		}
	}
	return op1Weight > op2Weight ? true : false;
}


void inputString(string exp)
{
	getline(cin, exp);
	cout << exp << endl;
}
int getSize(string exp)
{
	return exp.size();
}

template<class T>
struct node {
	node<T>* next;
	T data;
	node() :next(NULL) {}
	node(const T& d, node<T>* n) :data(d), next(n) {}
};

template<class T>
class calcStack {
private:
	node<T>* head;
public:
	calcStack()
	{
		head = NULL;
	}
	void push(const T& newData)
	{
		node<T>* n = new node<T>(newData, head);
		head = n;
	}
	void pop()
	{
		if (head == NULL)
		{
			cout << "the stack is empty" << endl;
		}
		else
		{
			node<T>* temp = head;
			head = head->next;
			//cout << "Deleting the first node with value " << temp->data << endl;
			delete temp;
		}
	}
	void show()
	{
		node<T>*curr;
		curr = head;
		while (curr != NULL)
		{
			cout << curr->data << " ";
			curr = curr->next;
		}
	}
	T& top()//??operator=
	{
		return head->data;
	}
	bool empty()
	{
		if (head == NULL)
		{
			return true;
		}
		return false;
	}
	void clear()
	{
		node<T>* temp = head;
		while (!empty())
		{
			pop();
		}
		pop();
	}
	T exponent(T num, T k)
	{
		return pow(num, k);
	}
	T squareRoot(T num)
	{
		return sqrt(num);
	}
	T naturalLogarithm(T num)
	{
		return log(num);
	}
	T sineOfDegrees(T num)
	{
		return sin(num*PI / 180);
	}
	T cosineOfDegrees(T num)
	{
		return cos(num*PI / 180);
	}
	T makeNegative(T num)
	{
		return (0 - num);
	}
	double numberOfDigits(T n)
	{
		double count = 0;
		while (n >= 1)
		{
			n /= 10;
			count += 1;
		}

		return count;
	}
	T numbrWithADecimalPoint(T n1, T n2)
	{
		double numOfDigits = numberOfDigits(n1);
		T del = pow(10, numOfDigits);
		n1 = n1 / del;
		T result;
		if (n2 >= 0)
		{
			result = n2 + n1;
		}
		else if (n2 < 0)
		{
			result = n2 - n1;
		}
		return result;
	}
	void handleNumber(int&i, string exp)//moje bi da go
	{
		int value = 0;
		while (isNumber(exp[i]))
		{
			value *= 10;
			value += (T)(exp[i] - 48);
			i++;
		}
		push(value);
	}

	void calculate(string exp)
	{
		calcStack<char>op;
		int size = getSize(exp);
		int index = 0;
		while (index < size)
		{
			if (exp[index] == ' '&& op.top() != '-')
			{
				index++;
				continue;
			}
			if (exp[index] == ' ' && op.top() == '-')
			{
				op.top() = 'n';
				index++;
			}
			if (exp[index] == '(')
			{
				op.push(exp[index]);
				index++;
			}
			if (IsFunction(exp[index]) && op.empty())
			{
				op.push(exp[index]);
				index++;
			}
			if (IsFunction(exp[index]) && op.top() == '(')
			{
				op.push(exp[index]);
				index++;
			}
			if (IsFunction(exp[index]) && !HasHigherPrecedence(op.top(), exp[index]))//&& num.top() != '('
			{
				op.push(exp[index]);
				index++;
			}

			if (IsOperator(exp[index]) && op.empty())
			{
				op.push(exp[index]);
				index++;
			}
			if (IsOperator(exp[index]) && op.top() == '(')//&& num.top() != '('
			{
				op.push(exp[index]);
				index++;
			}
			if (IsOperator(exp[index]) && !HasHigherPrecedence(op.top(), exp[index]))//&& num.top() != '('
			{
				op.push(exp[index]);
				index++;
			}
			if (IsOperator(exp[index]) && HasHigherPrecedence(op.top(), exp[index]))//&& num.top() != '('
			{
				char operation = op.top();
				op.pop();
				if (op.empty() || !HasHigherPrecedence(op.top(), exp[index]))
				{
					if (IsOperator(operation))
					{
						T num1 = top();
						pop();
						T num2 = top();
						pop();
						T result;
						if (operation == '+')
						{
							result = num1 + num2;
							push(result);
						}
						if (operation == '*')
						{
							result = num1 * num2;
							push(result);
						}
						if (operation == '-')
						{
							result = num2 - num1;
							push(result);
						}
						if (operation == '/')
						{
							result = num2 / num1;
							push(result);
						}
						if (operation == '^')
						{
							result = exponent(num2, num1);
							push(result);
						}
						if (operation == '.')
						{
							result = numbrWithADecimalPoint(num1, num2);
							push(result);
						}
					}
					if (IsFunction(operation))
					{
						T num1 = top();
						pop();
						T result;
						if (operation == 'r')
						{
							result = squareRoot(num1);
							push(result);
						}
						if (operation == 'l')
						{
							result = naturalLogarithm(num1);
							push(result);
						}
						if (operation == 's')
						{
							result = sineOfDegrees(num1);
							push(result);
						}
						if (operation == 'c')
						{
							result = cosineOfDegrees(num1);
							push(result);
						}
						if (operation == 'n')
						{
							result = makeNegative(num1);
							push(result);
						}
					}
				}
				if (!op.empty() && HasHigherPrecedence(op.top(), exp[index]))//e/g "r(9)*c(180)+5";
				{
					if (IsOperator(operation))
					{
						T num1 = top();
						pop();
						T num2 = top();
						pop();
						T result;
						if (operation == '+')
						{
							result = num1 + num2;
							push(result);
						}
						if (operation == '*')
						{
							result = num1 * num2;
							push(result);
						}
						if (operation == '-')
						{
							result = num2 - num1;
							push(result);
						}
						if (operation == '/')
						{
							result = num2 / num1;
							push(result);
						}
						if (operation == '^')
						{
							result = exponent(num2, num1);
							push(result);
						}
						if (operation == '.')
						{
							result = numbrWithADecimalPoint(num1, num2);
							push(result);
						}
					}
					if (IsFunction(operation))
					{
						T num1 = top();
						pop();
						T result;
						if (operation == 'r')
						{
							result = squareRoot(num1);
							push(result);
						}
						if (operation == 'l')
						{
							result = naturalLogarithm(num1);
							push(result);
						}
						if (operation == 's')
						{
							result = sineOfDegrees(num1);
							push(result);
						}
						if (operation == 'c')
						{
							result = cosineOfDegrees(num1);
							push(result);
						}
						if (operation == 'n')
						{
							result = makeNegative(num1);
							push(result);
						}
					}
					char operation2 = op.top();
					op.pop();
					if (IsOperator(operation2))
					{
						T num1 = top();
						pop();
						T num2 = top();
						pop();
						T result;
						if (operation2 == '+')
						{
							result = num1 + num2;
							push(result);
						}
						if (operation2 == '*')
						{
							result = num1 * num2;
							push(result);
						}
						if (operation2 == '-')
						{
							result = num2 - num1;
							push(result);
						}
						if (operation2 == '/')
						{
							result = num2 / num1;
							push(result);
						}
						if (operation2 == '^')
						{
							result = exponent(num2, num1);
							push(result);
						}
						if (operation2 == '.')
						{
							result = numbrWithADecimalPoint(num1, num2);
							push(result);
						}
					}
					if (IsFunction(operation2))
					{
						T num1 = top();
						pop();
						T result;
						if (operation2 == 'r')
						{
							result = squareRoot(num1);
							push(result);
						}
						if (operation2 == 'l')
						{
							result = naturalLogarithm(num1);
							push(result);
						}
						if (operation2 == 's')
						{
							result = sineOfDegrees(num1);
							push(result);
						}
						if (operation2 == 'c')
						{
							result = cosineOfDegrees(num1);
							push(result);
						}
						if (operation2 == 'n')
						{
							result = makeNegative(num1);
							push(result);
						}
					}

				}
				op.push(exp[index]);
				index++;
			}
			if (exp[index] == ')')
			{
				while (!op.empty() && op.top() != '(')
				{
					char operation = op.top();
					op.pop();
					if (IsOperator(operation))
					{
						T num1 = top();
						pop();
						T num2 = top();
						pop();
						T result;
						if (operation == '+')
						{
							result = num1 + num2;
							push(result);
						}
						if (operation == '*')
						{
							result = num1 * num2;
							push(result);
						}
						if (operation == '-')
						{
							result = num2 - num1;
							push(result);
						}
						if (operation == '/')
						{
							result = num2 / num1;
							push(result);
						}
						if (operation == '^')
						{
							result = exponent(num2, num1);
							push(result);
						}
						if (operation == '.')
						{
							result = numbrWithADecimalPoint(num1, num2);
							push(result);
						}
					}
					if (IsFunction(operation))
					{
						T num1 = top();
						pop();
						T result;
						if (operation == 'r')
						{
							result = squareRoot(num1);
							push(result);
						}
						if (operation == 'l')
						{
							result = naturalLogarithm(num1);
							push(result);
						}
						if (operation == 's')
						{
							result = sineOfDegrees(num1);
							push(result);
						}
						if (operation == 'c')
						{
							result = cosineOfDegrees(num1);
							push(result);
						}
						if (operation == 'n')
						{
							//op.pop();//za da mahna i otvarqshtata skoba (
							result = makeNegative(num1);
							push(result);
						}
					}
				}
				index++;
				op.pop();
			}
			if (IsOperand(exp[index]))
			{
				handleNumber(index, exp);//index-ut se promenq v handleNumber
			}
		}
		while (!op.empty())
		{
			char operation = op.top();
			op.pop();
			if (IsOperator(operation))
			{
				T num1 = top();
				pop();
				T num2 = top();
				pop();
				T result;
				if (operation == '+')
				{
					result = num1 + num2;
					push(result);
				}
				if (operation == '*')
				{
					result = num1 * num2;
					push(result);
				}
				if (operation == '-')
				{
					result = num2 - num1;
					push(result);
				}
				if (operation == '/')
				{
					result = num2 / num1;
					push(result);
				}
				if (operation == '^')
				{
					result = exponent(num2, num1);
					push(result);
				}
				if (operation == '.')
				{
					result = numbrWithADecimalPoint(num1, num2);
					push(result);
				}
			}
			if (IsFunction(operation))
			{
				T num1 = top();
				pop();
				T result;
				if (operation == 'r')
				{
					result = squareRoot(num1);
					push(result);
				}
				if (operation == 'l')
				{
					result = naturalLogarithm(num1);
					push(result);
				}
				if (operation == 's')
				{
					result = sineOfDegrees(num1);
					push(result);
				}
				if (operation == 'c')
				{
					result = cosineOfDegrees(num1);
					push(result);
				}
				if (operation == 'n')
				{
					result = makeNegative(num1);
					push(result);
				}
			}
		}
		//cout << "the result is: " << top() << endl;
	}
};


int main()
{
	//string exp = "34*10-20/5";
	//string exp = "10-5*5";
	//string exp = "((10+5)*2)/3";
	//string exp = "(17+3)^2";
	//string exp = "r(90+10)+5";
	//string exp = "r(r(4*4))+5";
	//string exp = "r(5+r(16))";
	//string exp = "20/r(110-10)";
	//string exp = "l(r(100))";
	//string exp = "r(10)+2";
	//string exp = "l(s(180)+c(0)+c(0))*3";
	//string exp = "(- 2)*r(9)-4";
	//string exp = "(- 2)+3*4";
	//string exp = "(- 2)^3";
	//string exp = "r(9)*c(180)+5";
	//string exp = "s(r(4*4-7))";
	//string exp = "10.3/5. 7";
	//string exp = "r(10.3)*c(180)+5.2";
	//string exp = "3*13.45-2";
	//string exp = "925*2.5+18/4.5*4-10*3^3";//2058,5
	//string exp = "(- 4.7)*r(2+2)*205/(- 15)";
	//string exp = "r(4.5+4.5)^2.3";
	cout << "You can choose between theese operations: + , - , * , / ." << endl;
	cout << "For the exponent of a number choose '^'." << endl;
	cout << "For a negative number write it like this: if the number is 'x' you should write (- x)." << endl;
	cout << "For the square root of a number choose 'r'." << endl;
	cout << "For the sin of a number choose 's'." << endl;
	cout << "For the cos of a number choose 'c'." << endl;
	cout << "For the log of a number choose 'l'." << endl;
	string exp;
	cout << "Write the expression that you want to be calculated: " << endl;
	cin >> exp;
	calcStack<float> s;
	s.calculate(exp);
	string a;
	cout << "If you want to see the result write '='." << endl;
	cout << "If you need help write 'help'." << endl;
	cout << "If you want to quit the program write 'quit'." << endl;
	cout << "If you want to delete everything up to now write 'clear''." << endl;
	while (cin >> a) {
		if (a == "=")
		{
			cout << s.top() << endl;
		}
		if (a == "clear")
		{
			s.clear();
		}
		if (a == "show")
		{
			s.clear();
		}
		if (a == "help")
		{
			cout << "Look carefully if you have made a mistake" << endl;
		}
		if (a == "quit")
		{
			exit(0);
		}
	}



	//return 0;
}



