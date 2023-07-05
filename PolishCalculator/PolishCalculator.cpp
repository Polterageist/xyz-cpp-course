#include <iostream>

int main()
{
	std::cout << "Enter operation (+ - / *) and operands in format op a b!\n";
	std::string operation;
	double a = 0.;
	double b = 0.;
	std::cin >> operation >> a >> b;
	double result = 0.;
	if (operation == "+")
	{
		result = a + b;
	}
	else if (operation == "-")
	{
		result = a - b;
	}
	else if (operation == "*")
	{
		result = a * b;
	}
	else if (operation == "/")
	{
		result = a / b;
	}
	else
	{
		std::cout << "Unknown operation: " << operation << "\n";
	}

	std::cout << "Result: " << result << "\n";
}
