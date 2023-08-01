#include "LearnSearchAndStd.h"
#include "Stats.h"
#include <iostream>
#include "LearnAssymptoticAnalysis.h"
#include <algorithm>

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
	int maxNumber = 1;
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

void LearnStdIterators()
{
	std::cout << "Learn std iterators" << std::endl;

	const int arraySize = 10;
	int staticArray[arraySize];
	for (int i = 0; i < arraySize; ++i)
	{
		staticArray[i] = i;
	}

	std::cout << "Static array printed from iterator: ";
	for (auto it = std::begin(staticArray); it != std::end(staticArray); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	std::cout << "Static array printed in reverse order: ";
	for (auto it = std::rbegin(staticArray); it != std::rend(staticArray); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	std::cout << "Each even element of array: ";
	for (auto it = std::begin(staticArray); it != std::end(staticArray); it += 2)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	std::cout << "Calculated array size = " << std::distance(std::begin(staticArray), std::end(staticArray)) << std::endl;

	std::cout << std::endl;
}

void LearnStdAlgo()
{
	std::cout << "Learn some useful std algorythms" << std::endl;
	const int arraySize = 10;
	int staticArray[arraySize];
	for (int i = 0; i < arraySize; ++i)
	{
		staticArray[i] = i;
	}
	std::cout << "Static array: ";
	for (auto it = std::begin(staticArray); it != std::end(staticArray); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	// Linear searcch
	auto it = std::find(std::begin(staticArray), std::end(staticArray), 5);
	std::cout << "Found element 5 at index " << std::distance(std::begin(staticArray), it) << std::endl;

	it = std::find(std::begin(staticArray), std::end(staticArray), 11);
	if (it == std::end(staticArray))
	{
		std::cout << "Element 11 not found" << std::endl;
	}

	staticArray[5] = 4;
	// Binary search, which finds first and last element, which are equal to the searched element
	auto range = std::equal_range(std::begin(staticArray), std::end(staticArray), 4);
	std::cout << "Found range of elements equal to 4: [" << std::distance(std::begin(staticArray), range.first) << ", " << std::distance(std::begin(staticArray), range.second) << ")" << std::endl;

	// Check if array is sorted
	bool isSorted = std::is_sorted(std::begin(staticArray), std::end(staticArray));
	std::cout << "Is array sorted: " << isSorted << std::endl;
	
	// Shuffle array
	std::random_shuffle(std::begin(staticArray), std::end(staticArray));
	isSorted = std::is_sorted(std::begin(staticArray), std::end(staticArray));
	std::cout << "Is modified array sorted: " << isSorted << std::endl;

	// Sort array
	std::sort(std::begin(staticArray), std::end(staticArray));
	isSorted = std::is_sorted(std::begin(staticArray), std::end(staticArray));
	std::cout << "Is sorted array sorted: " << isSorted << std::endl;

	std::cout << std::endl;
}

void LearnSearchAndStd()
{
	std::cout << "Learn search and std" << std::endl;
	CalculateBinarySearchStats();
	LearnStdIterators();
	LearnStdAlgo();
	std::cout << std::endl;
}
