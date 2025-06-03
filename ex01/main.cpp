#include <iostream>
#include <stack>

void fulling(std::stack<int> *myStack, char c)
{
	if (isdigit(c))
	{
		myStack->push(c - '0');
	}
}

int calcul(std::stack<int> &myStack, char c)
{
	
	if (!isdigit(c) && c != ' ')
	{
		if(myStack.size() < 2)
			return std::cerr << "Error: not enough operands in stack" << std::endl, 1;
		int a = myStack.top();
		myStack.pop();
		int b = myStack.top();
		myStack.pop(); 
		if(c == '+')
			myStack.push(b + a);
		if(c == '-')
			myStack.push(b - a);
		if(c == '*')
			myStack.push(b * a);
		if(c == '/')
		{
			if (b == 0)
				return std::cerr << "Error: division by zero" << std::endl, 1;
			myStack.push(b / a);
		}
	}
	return 0;
}

int main(int argc, char** argv)
{
	if (argc != 2)
		return std::cerr << "Error" << std::endl, 1;

	std::stack<int> *myStack = new std::stack<int>;
	int i = 0;
	while (argv[1][i])
	{
		if (i % 2 == 1 && argv[1][i] != ' ')
			return delete myStack, std::cerr << "Error 1" << std::endl, 1;
		if (i % 2 == 0 && (!isdigit(argv[1][i]) 
			&& argv[1][i] != '*'
			&& argv[1][i] != '/'
			&& argv[1][i] != '+'
			&& argv[1][i] != '-'))
			return delete myStack, std::cerr << "Error 2" << std::endl, 1;
		if (!isdigit(argv[1][0]) || !isdigit(argv[1][2]))
			return delete myStack, std::cerr << "Error 3" << std::endl, 1;
		fulling(myStack, argv[1][i]);
		if (i > 3)
			if (calcul(*myStack, argv[1][i]))
				return (delete myStack, 1);
		i++;
	}
	std::cout << myStack->top() << std::endl;
	delete myStack;
}