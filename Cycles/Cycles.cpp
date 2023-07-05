#include <iostream>
#include <sstream>

const unsigned int NUMBER_OF_BOXES = 20;

int main()
{
	std::cout << "Do you want to play? (y/n)\n";
	std::string answer;
	std::cin >> answer;
	if (answer == "y")
	{
		std::cout << "Buy an elephant\n";

		bool shouldContinue = true;
		while (shouldContinue)
		{
			std::getline(std::cin, answer);
			if (answer == "ENOUGH!!!")
			{
				shouldContinue = false;
			}
			else
			{
				std::cout << "Everyone say \"" << answer << "\", but by an elephant\n";
			}
		}
	}
	
	std::cout << "Are you sure? (y/n)\n";
	std::cin >> answer;
	if (answer != "y")
	{
		do
		{
			std::cout << answer << "\n";
			std::getline(std::cin, answer);
		} while (answer != "stop");
	}

	std::cout << "Enter a number: ";
	int number = 0;
	std::cin >> number;
	int sum = 0;
	for (int i = 1; i <= number; ++i)
	{
		sum += i;
	}
	std::cout << "Sum of first " << number << " integers is: " << sum << "\n";

	int boxes[NUMBER_OF_BOXES];
	for (int i = 0; i < NUMBER_OF_BOXES; ++i)
	{
		boxes[i] = NUMBER_OF_BOXES - i;
	}

	std::cout << "Unsorted boxes: ";
	for (int i : boxes)
	{
		std::cout << i << " ";
	}
	std::cout << "\n";

	// Bubble sort
	for (int i = 0; i < NUMBER_OF_BOXES; ++i)
	{
		for (int j = 0; j < NUMBER_OF_BOXES - 1; ++j)
		{
			if (boxes[j] > boxes[j + 1])
			{
				int temp = boxes[j];
				boxes[j] = boxes[j + 1];
				boxes[j + 1] = temp;
			}
		}
	}

	std::cout << "Sorted boxes: ";
	for (int i : boxes)
	{
		std::cout << i << " ";
	}
	std::cout << "\n";

	// Infinite loop
	while (true)
	{
		std::cout << "I'm infinite!\n";
		while (true)
		{
			std::cout << "\tI'm infinite, but you can break me: ";
			std::cin >> answer;
			if (answer == "break")
			{
				break;
			}
		}
	}
}

