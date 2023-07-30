#include "TuringMachine.h"
#include <iostream>
#include <cassert>

void InitTuringMachine(TuringMachine& turingMachine, int initialState, const char* tape, const Rule* rules, int rulesSize)
{
	ShutdownTuringMachine(turingMachine);

	assert(initialState >= 0);
	assert(tape != nullptr);
	assert(rules != nullptr &&rulesSize > 0);

	turingMachine.state = initialState;
	turingMachine.tapeSize = strlen(tape) + 1;
	turingMachine.tape = new char[turingMachine.tapeSize];
	turingMachine.position = 0;
	
	memset(turingMachine.tape, EMPTY_SYMBOL, turingMachine.tapeSize);
	memcpy(turingMachine.tape, tape, turingMachine.tapeSize);

	turingMachine.rules = new Rule[rulesSize];
	turingMachine.rulesSize = rulesSize;
	turingMachine.lastRule = -1;

	memcpy(turingMachine.rules, rules, rulesSize * sizeof(Rule));

	turingMachine.steps = 0;
}

void ShutdownTuringMachine(TuringMachine& turingMachine)
{
	if (turingMachine.tape)
	{
		delete[] turingMachine.tape;
		turingMachine.tape = nullptr;
		turingMachine.tapeSize = 0;
	}
	if (turingMachine.rules)
	{
		delete[] turingMachine.rules;
		turingMachine.rules = nullptr;
		turingMachine.rulesSize = 0;
	}

	turingMachine.state = HALT_STATE;
	turingMachine.position = -1;
	turingMachine.steps = 0;
}

void RunTuringMachine(TuringMachine& turingMachine, int numSteps)
{
	if (turingMachine.state == HALT_STATE || turingMachine.state == ERROR_STATE)
	{
		return;
	}

	if (numSteps <= 0)
	{
		return;
	}

	int steps = turingMachine.steps;
	while (turingMachine.state != HALT_STATE && turingMachine.steps - steps < numSteps)
	{
		// Find rule
		Rule* rule = nullptr;
		for (int i = 0; i < turingMachine.rulesSize; i++)
		{
			if (turingMachine.rules[i].state == turingMachine.state && turingMachine.rules[i].symbol == turingMachine.tape[turingMachine.position])
			{
				rule = &turingMachine.rules[i];
				turingMachine.lastRule = i;
				break;
			}
		}
		if (rule == nullptr)
		{
			turingMachine.state = ERROR_STATE;
			break;
		}
		// Apply rule
		turingMachine.state = rule->newState;
		turingMachine.tape[turingMachine.position] = rule->newSymbol;
		turingMachine.position += (int)rule->direction;

		// Resize tape if needed
		if (turingMachine.position < 0 || turingMachine.position == turingMachine.tapeSize - 1)
		{
			int newTapeSize = turingMachine.tapeSize + 1;
			int offset = turingMachine.position < 0 ? 1 : 0;
			char* newTape = new char[newTapeSize];
			memset(newTape, EMPTY_SYMBOL, newTapeSize); 
			memcpy(newTape + offset, turingMachine.tape, turingMachine.tapeSize - 1);
			newTape[newTapeSize - 1] = 0;
			delete[] turingMachine.tape;
			turingMachine.tape = newTape;
			turingMachine.tapeSize = newTapeSize;
			turingMachine.position = turingMachine.position + offset;
		}

		turingMachine.steps++;
	}
}

void PrintTuringMachine(TuringMachine& turingMachine)
{
	std::cout << "State: " << turingMachine.state << std::endl;
	std::cout << "Tape: ";
	for (int i = 0; i < turingMachine.tapeSize; i++)
	{
		if (i == turingMachine.position)
		{
			std::cout << ">";
		}
		std::cout << turingMachine.tape[i];
		if (i == turingMachine.position)
		{
			std::cout << "<";
		}
	}
	std::cout << std::endl;
	std::cout << "Rules: " << std::endl;
	for (int i = 0; i < turingMachine.rulesSize; i++)
	{
		if (i == turingMachine.lastRule)
		{
			std::cout << "> ";
		}
		else 
		{
			std::cout << "  ";
		}
		std::cout << turingMachine.rules[i].state << " '" << turingMachine.rules[i].symbol << "' -> " << turingMachine.rules[i].newState << " '" << turingMachine.rules[i].newSymbol << "' " << (turingMachine.rules[i].direction == Direction::Left ? "<<" : ">>") << std::endl;
	}
	std::cout << "Steps: " << turingMachine.steps << std::endl;
	std::cout << "Used memory: " << turingMachine.tapeSize << std::endl;
}
