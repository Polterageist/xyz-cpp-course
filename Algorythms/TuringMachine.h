#pragma once

const int HALT_STATE = -1;
const int ERROR_STATE = -2; // When no rule is found and it is not halt
const char EMPTY_SYMBOL = '_';

enum class Direction
{
	Left = -1,
	Right = 1
};

struct Rule
{
	int state;
	char symbol;
	int newState;
	char newSymbol;
	Direction direction;
};

struct TuringMachine
{
	int state = HALT_STATE;
	int position = -1;
	char* tape = nullptr;
	int tapeSize = 0;
	Rule* rules = nullptr;
	int rulesSize;
	int lastRule = -1;
	int steps = 0;
};

void InitTuringMachine(TuringMachine& turingMachine, int initialState, const char* tape, const Rule* rules, int rulesSize);
void ShutdownTuringMachine(TuringMachine& turingMachine);
void RunTuringMachine(TuringMachine& turingMachine, int numSteps);
void PrintTuringMachine(TuringMachine& turingMachine);
