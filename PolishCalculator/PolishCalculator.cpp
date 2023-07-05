#include <iostream>

int main()
{
	bool shouldContinue = true;
	while (shouldContinue)
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

		std::cout << "Do you want to continue? (y/n)\n";
		std::string answer;
		std::cin >> answer;
		shouldContinue = answer == "y";
	}
}
