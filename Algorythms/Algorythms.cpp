#include <iostream>
#include "TuringMachine.h"
#include <assert.h>

void learnHelloWorldWithTuringMachine()
{
	std::cout << "Learn Hello World with Turing Machine" << std::endl;
    TuringMachine turingMachine;
    
    // Print Hello World to tape
    const char tape[] = "_";
    const Rule rules[] = 
    {
		{ 0, EMPTY_SYMBOL, 1, 'H', Direction::Right },
		{ 1, EMPTY_SYMBOL, 2, 'e', Direction::Right },
		{ 2, EMPTY_SYMBOL, 3, 'l', Direction::Right },
		{ 3, EMPTY_SYMBOL, 4, 'l', Direction::Right },
		{ 4, EMPTY_SYMBOL, 5, 'o', Direction::Right },
		{ 5, EMPTY_SYMBOL, 6, ' ', Direction::Right },
		{ 6, EMPTY_SYMBOL, 7, 'W', Direction::Right },
		{ 7, EMPTY_SYMBOL, 8, 'o', Direction::Right },
		{ 8, EMPTY_SYMBOL, 9, 'r', Direction::Right },
		{ 9, EMPTY_SYMBOL, 10, 'l', Direction::Right },
		{ 10, EMPTY_SYMBOL, 11, 'd', Direction::Right },
		{ 11, EMPTY_SYMBOL, HALT_STATE, '!', Direction::Right },
	};
	
	InitTuringMachine(turingMachine, 0, tape, rules, sizeof(rules) / sizeof(Rule));
	// Print the initial state
	std::cout << "Initial:" << std::endl;
	PrintTuringMachine(turingMachine);
	std::cout << std::endl;

	// Run the machine, printing the tape at each step
	while (turingMachine.state != HALT_STATE)
	{
		std::cout << "Step " << turingMachine.steps << ":" << std::endl;
		RunTuringMachine(turingMachine, 1);
		PrintTuringMachine(turingMachine);
		std::cout << std::endl;
	}

	// Print the final state
	std::cout << "Result:" << std::endl;
	PrintTuringMachine(turingMachine);

	// Shutdown the machine
	ShutdownTuringMachine(turingMachine);

	std::cout << std::endl;
}

std::string invertStringWithTuringMachine(const std::string& input)
{
	// Simplified version which works only for strings of 0 and 1
	assert(input.length() >= 1);
	assert(input.find_first_not_of("01") == std::string::npos);

	TuringMachine turingMachine;
	const char* tape = input.c_str(); // We will not modify the input string

	const Rule rules[] =
	{
		// Save symbol under the cursor, erase and go right
		{ 0, '0', 1, EMPTY_SYMBOL, Direction::Right },
		{ 0, '1', 2, EMPTY_SYMBOL, Direction::Right },
		// Skip symbols
		{ 1, '0', 1, '0', Direction::Right },
		{ 1, '1', 1, '1', Direction::Right },
		{ 2, '0', 2, '0', Direction::Right },
		{ 2, '1', 2, '1', Direction::Right },
		// We found the empty space. Insert saved symbol here and go left
		{ 1, EMPTY_SYMBOL, 3, '0', Direction::Left },
		{ 2, EMPTY_SYMBOL, 3, '1', Direction::Left },
		// Save symbol under the cursor, erase and go left
		{ 3, '0', 4, EMPTY_SYMBOL, Direction::Left },
		{ 3, '1', 5, EMPTY_SYMBOL, Direction::Left },
		// If we are on empty symbol - halt
		{ 3, EMPTY_SYMBOL, HALT_STATE, EMPTY_SYMBOL, Direction::Left },
		// Skip symbols
		{ 4, '0', 4, '0', Direction::Left },
		{ 4, '1', 4, '1', Direction::Left },
		{ 5, '0', 5, '0', Direction::Left },
		{ 5, '1', 5, '1', Direction::Left },
		// We found the empty symbol. Insert saved symbol here and go right
		{ 4, EMPTY_SYMBOL, 0, '0', Direction::Right },
		{ 5, EMPTY_SYMBOL, 0, '1', Direction::Right },
		// If we are on empty symbol - halt
		{ 0, EMPTY_SYMBOL, HALT_STATE, EMPTY_SYMBOL, Direction::Right},
	};

	InitTuringMachine(turingMachine, 0, tape, rules, sizeof(rules) / sizeof(Rule));

	// Print the initial state
	/*std::cout << "Initial:" << std::endl;
	PrintTuringMachine(turingMachine);
	std::cout << std::endl;*/

	// Run the machine, printing the tape at each step
	while (turingMachine.state >= 0)
	{
		RunTuringMachine(turingMachine, 1);

		//std::cout << "Step:" << std::endl;
		//PrintTuringMachine(turingMachine);
		//std::cout << std::endl;
	}

	//// Print the final state
	//std::cout << "Result:" << std::endl;
	//PrintTuringMachine(turingMachine);
	
	// Print stats:
	std::cout << "Used " << turingMachine.steps << " steps" << std::endl;
	std::cout << "Used " << turingMachine.tapeSize - 1 << " bytes" << std::endl;

	std::string result;
	for (int i = 0; i < turingMachine.tapeSize; i++)
	{
		if (turingMachine.tape[i] != EMPTY_SYMBOL)
		{
			result += turingMachine.tape[i];
		}
	}

	ShutdownTuringMachine(turingMachine);

	return result;
}

// Equivalent in C++
std::string invertStringWithCpp(const std::string& input)
{
	std::string memory = input + EMPTY_SYMBOL;
	int cursor = 0;
	int steps = 0;

	char savedSymbol = '\0'; // State
	while (true)
	{
		savedSymbol = memory[cursor];
		memory[cursor] = EMPTY_SYMBOL;
		++cursor;
		++steps;
		
		while (memory[cursor] != EMPTY_SYMBOL)
		{
			++cursor;
			++steps;
		}

		memory[cursor] = savedSymbol;
		--cursor;
		if (memory[cursor] == EMPTY_SYMBOL)
		{
			break;
		}
		++steps;

		savedSymbol = memory[cursor];
		memory[cursor] = EMPTY_SYMBOL;
		--cursor;
		++steps;

		while (memory[cursor] != EMPTY_SYMBOL)
		{
			--cursor;
			++steps;
		}

		memory[cursor] = savedSymbol;
		++cursor;
		if (memory[cursor] == EMPTY_SYMBOL)
		{
			break;
		}
		++steps;
	}

	// Print stats
	std::cout << "Used " << steps << " steps" << std::endl;
	std::cout << "Used " << memory.size() << " bytes" << std::endl;

	std::string result;
	for (int i = 0; i < memory.length(); i++)
	{
		if (memory[i] != EMPTY_SYMBOL)
		{
			result += memory[i];
		}
	}

	return result;
}

// Faster version in C++, but with more states
std::string invertStringWithCppFast(const std::string& input)
{
	// Don't count it as a step
	std::string result = input;

	int steps = 0;

	// Calculate length
	int length = 0;
	while (input[length] != '\0')
	{
		++length;
		++steps;
	}

	for (int i = length; i > length / 2; --i)
	{
		// Swap
		char temp = result[i - 1];
		++steps;
		result[i - 1] = result[length - i];
		++steps;
		result[length - i] = temp;
		++steps;
	}

	// Print stats
	std::cout << "Used " << steps << " steps" << std::endl;
	std::cout << "Used " << result.size() + sizeof(length) << " bytes" << std::endl;

	return result;
}


void learnNontrivialTuringMachine()
{
	std::cout << "Learn non trivial Turing machine" << std::endl;
	
	std::string input;
	do 
	{
		std::cout << "Enter sequence of 0 and 1: " << std::endl;
		std::cin >> input;
		if (input.find_first_not_of("01") != std::string::npos)
		{
			break;
		}

		std::cout << "Length of the input:" << input.length() << std::endl;

		std::cout << "Invert with Turing machine:" << std::endl;
		std::string result = invertStringWithTuringMachine(input);
		std::cout << "Result of inverting \"" << input << "\": \"" << result << "\"" << std::endl;

		std::cout << std::endl;

		std::cout << "Invert with c++ function:" << std::endl;
		result = invertStringWithCpp(input);
		std::cout << "Result of inverting \"" << input << "\": \"" << result << "\"" << std::endl;

		std::cout << std::endl;

		std::cout << "Invert with fast c++ function:" << std::endl;
		result = invertStringWithCppFast(input);
		std::cout << "Result of inverting \"" << input << "\": \"" << result << "\"" << std::endl;
		std::cout << std::endl;
	} while (input.length() != 0);

	std::cout << std::endl;
}

int main()
{
	learnHelloWorldWithTuringMachine();
	learnNontrivialTuringMachine();
}
