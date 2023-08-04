#include "LearnFIFOLIFO.h"
#include <iostream>
#include <vector>
#include <string>

void LearnLIFO()
{
	std::cout << "LearnLIFO" << std::endl;

	// Count brackets
	std::cout << "Enter sequence with brackets: ";
	std::string sequence;
	std::cin >> sequence;
	std::vector<size_t> stack;
	int numEnclosedSequences = 0;
	for (size_t i = 0; i < sequence.size(); ++i)
	{
		if (sequence[i] == '(')
		{
			stack.push_back(i);
			++numEnclosedSequences;
		}
		else if (sequence[i] == ')')
		{
			if (stack.empty())
			{
				std::cout << "Error: no opening bracket for closing bracket at position " << i << std::endl;
				return;
			}
			stack.pop_back();
		}
	}
	if (!stack.empty())
	{
		std::cout << "Error: no closing bracket for opening bracket at position " << stack.back() << std::endl;
	}
	else
	{
		std::cout << "Number of enclosed sequences: " << numEnclosedSequences << std::endl;
	}
	
	std::cout << std::endl;
}

void LearnFIFO()
{
	std::cout << "LearnFIFO" << std::endl;

	std::cout << "Provider generates numbers from 0 to 99 and consumer echoing it" << std::endl;
	// Imitation of parallel work of providers and consumers
	std::vector<int> queue;
	for(int i = 0; i < 10; ++i)
	{
		int providerSpeed = rand() % 2 + 1;
		int consumerSpeed = rand() % 2 + 1;
		// Provider
		for (int j = 0; j < providerSpeed; ++j)
		{
			int num = rand() % 100;
			queue.push_back(num);
			std::cout << "Generated: " << num << std::endl;
		}
		// Consumer
		for (int j = 0; j < consumerSpeed; ++j)
		{
			if (!queue.empty())
			{
				std::cout << "Echo: " << queue.front() << std::endl;
				queue.erase(queue.begin());
			}
			else
			{
				break;
			}
		}
	}
	// Consumer
	while (!queue.empty())
	{
		std::cout << "Echo: " << queue.front() << std::endl;
		queue.erase(queue.begin());
	}

	std::cout << std::endl;
}

void LearnFIFOLIFO()
{
	std::cout << "LearnFIFOLIFO" << std::endl;

	LearnLIFO();
	LearnFIFO();

	std::cout << std::endl;
}
