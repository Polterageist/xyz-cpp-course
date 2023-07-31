#include "LearnSearchAndStd.h"
#include "Stats.h"
#include <iostream>
#include "LearnAssymptoticAnalysis.h"

// Time: best: O(1), worst: O(log(N)), Memory: O(1)
int BinarySearch(int* array, int arraySize, int elem, Stats& stats)
{
	InitStats(stats);
	stats.dataLength = arraySize;

	int result = -1;
	int left = 0;
	int right = arraySize - 1;
	while (left <= right)
	{
		stats.steps += 1;
		int mid = (left + right) / 2;
		if (array[mid] == elem)
		{
			result = mid;
			break;
		}
		else if (array[mid] < elem)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
		
	}
	stats.memory = 3 * sizeof(int);

	return result;
}

void CalculateBinarySearchStats()
{
	const int arraySize = 100;
	int array[arraySize];

	std::cout << "Calculating stats for binary search...\n";

	// Produce sorted array
	std::cout << "Array: [";
	int maxNumber = 0;
	for (int i = 0; i < arraySize; ++i)
	{
		array[i] = maxNumber + rand() % 4;
		if (array[i] > maxNumber)
		{
			maxNumber = array[i];
		}

		std::cout << array[i];
		if (i < arraySize - 1)
		{
			std::cout << ", ";
		}
	}
	std::cout << "]\n";

	MultiStats<2> stats;
	stats.statNames[0] = "Linear search";
	stats.statNames[1] = "Binary search";
	stats.stats.resize(arraySize);
	for (int actualSize = 1; actualSize <= arraySize; ++actualSize)
	{
		int number = rand() % array[actualSize - 1] + 1;
		auto& localStats = stats.stats[actualSize - 1];
		int linIndex = FindArrayItemIndex(array, actualSize, number, localStats[0]);
		int binIndex = BinarySearch(array, actualSize, number, localStats[1]);
		std::cout << "Number: " << number;
		std::cout << ", Linear search index: " << linIndex;
		std::cout << ", Binary search index: " << binIndex;
		std::cout << std::endl;
	}

	WriteMultipleStatsCSV("BinarySearchStats.csv", stats);
	std::cout << "Results saved to BinarySearchStats.csv\n";
	std::cout << std::endl;
}

void LearnSearchAndStd()
{
	std::cout << "Learn search and std" << std::endl;
	CalculateBinarySearchStats();
	std::cout << std::endl;
}
