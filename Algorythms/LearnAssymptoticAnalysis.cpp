#include "LearnAssymptoticAnalysis.h"
#include "Stats.h"

// TIme complexity: O(1), Memory complexity: O(1)
int GetArrayElem(int array[], size_t arraySize, size_t index, Stats& stats)
{
	InitStats(stats);
	stats.dataLength = arraySize;
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
size_t FindArrayItemIndex(int array[], size_t arraySize, int item, Stats& stats)
{
	InitStats(stats);
	stats.dataLength = arraySize;
	stats.memory = arraySize * sizeof(int);
	for (size_t i = 0; i < arraySize; ++i)
	{
		++stats.steps;
		if (array[i] == item)
		{
			return i;
		}
		++stats.steps;
	}
	stats.memory = sizeof(int);
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

void LearnAssymptoticAnalysis()
{
	std::cout << "Learn Asymptotic Analysis" << std::endl;

	CalculateDifferentStats();

	std::cout << std::endl;
}
