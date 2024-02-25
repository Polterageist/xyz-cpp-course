#include "LearnAssymptoticAnalysis.h"
#include "Stats.h"

// TIme complexity: O(1), Memory complexity: O(1)
int GetArrayElem(int array[], size_t arraySize, size_t index, Stats& stats)
{
	InitStats(stats);
	stats.dataLength = (int)arraySize;
	if (arraySize <= index)
	{
		++stats.steps;
		return 0;
	}
	++stats.steps;

	int result = *(array + index);
	stats.memory = 0;
	++stats.steps;

	return result;
}

// Time complexity: O(n), Memory complexity: O(1)
int FindArrayItemIndex(int array[], int arraySize, int item, struct Stats& stats)
{
	InitStats(stats);
	stats.dataLength = arraySize;
	stats.memory = sizeof(int);
	for (int i = 0; i < arraySize; ++i)
	{
		++stats.steps;
		if (array[i] == item)
		{
			return i;
		}
	}
	
	return -1;
}

template <class T>
T FindArrayItemIndex(T array[], int arraySize, T item, struct Stats& stats)
{
	InitStats(stats);
	stats.dataLength = arraySize;
	stats.memory = sizeof(int);
	for (int i = 0; i < arraySize; ++i)
	{
		++stats.steps;
		if (array[i] == item)
		{
			return i;
		}
	}

	return -1;
}


// Time complexity: O(n), Memory complexity: O(1)
void BubbleSort(int array[], int arraySize, Stats& stats)
{
	InitStats(stats);
	stats.dataLength = arraySize;

	for (int i = 0; i < arraySize; ++i)
	{
		for (int j = 0; j < arraySize - i - 1; ++j)
		{
			++stats.steps;
			if (array[j] > array[j + 1])
			{
				++stats.steps;
				int temp = array[j];
				++stats.steps;
				array[j] = array[j + 1];
				++stats.steps;
				array[j + 1] = temp;
				++stats.steps;
			}
		}
	}
	stats.memory = 3 * sizeof(int);
}

void CalculateDifferentStats()
{
	MultiStats<3> stats;
	stats.statNames[0] = "Get array elem";
	stats.statNames[1] = "Find element";
	stats.statNames[2] = "Bubble sort";

	const int NUM_TESTS = 100;
	int array[NUM_TESTS];

	std::cout << "Calculate stats for " << NUM_TESTS << " length variations..." << std::endl;

	stats.stats.resize(NUM_TESTS);
	for (int i = 0; i < NUM_TESTS; ++i)
	{
		int arraySize = i + 1;
		for (int j = 0; j < arraySize; ++j)
		{
			array[j] = rand();
		}
		auto& testStats = stats.stats[i];

		GetArrayElem(array, arraySize, 0, testStats[0]);
		FindArrayItemIndex(array, arraySize, 0, testStats[1]);
		BubbleSort(array, arraySize, testStats[2]);
	}

	WriteMultipleStatsCSV("FewAlgorythmsStats.csv", stats);
	std::cout << "Results are written to FewAlgorythmsStats.csv" << std::endl;
}

// Time complexity: n^2, Memory complexity: n
int FindNthSimpleNumber(int n, Stats& stats)
{
	InitStats(stats);
	stats.dataLength = n;
	int i = 0;

	if (n == 0)
	{
		++stats.steps;
		return 2;
	}
	else if(n == 1)
	{
		++stats.steps;
		return 3;
	}

	std::vector<int> simpleNumbers;
	simpleNumbers.push_back(2);
	simpleNumbers.push_back(3);
	++stats.steps;
	++stats.memory;
	for (int i = 2; i <= n; ++i)
	{
		++stats.steps;
		int number = simpleNumbers[i - 1] + 2; // We know that next simple number is odd
		++stats.steps;
		while (true)
		{
			++stats.steps;
			bool isSimple = true;
			++stats.steps;
			for (int j = 1; j < i; ++j)
			{
				++stats.steps;
				if (number % simpleNumbers[j] == 0)
				{
					isSimple = false;
					++stats.steps;
					break;
				}
				++stats.steps;
			}
			++stats.steps;
			if (isSimple)
			{
				simpleNumbers.push_back(number);
				++stats.steps;
				++stats.memory;
				break;
			}
			++stats.steps;
			number += 2;
		}
		++stats.steps;
	}

	return simpleNumbers[n];
}

void CalculateSimpleNumbersStats()
{
	std::cout << "Calculate 100 simple numbers:" << std::endl;

	Stats stats[100];
	for (int i = 0; i < 100; ++i)
	{
		int simpleNumber = FindNthSimpleNumber(i, stats[i]);
		std::cout << "Simple number #" << i << " is " << simpleNumber << std::endl;
	}

	WriteStatsCSV("SimpleNumbersStats.csv", stats, 100);
	std::cout << "Stats are written to SimpleNumbersStats.csv" << std::endl;
	std::cout << std::endl;
}

void LearnAssymptoticAnalysis()
{
	std::cout << "Learn Asymptotic Analysis" << std::endl;

	CalculateDifferentStats();
	CalculateSimpleNumbersStats();

	std::cout << std::endl;
}
