#include "LearnSorts.h"
#include "LearnAssymptoticAnalysis.h"
#include "Stats.h"
#include <iostream>

void QuickSort(int array[], int arraySize, Stats& stats)
{
	stats.dataLength = arraySize;

	++stats.steps;
	if (arraySize <= 1)
	{
		return;
	}

	int pivot = array[arraySize / 2];
	int* left = array;
	int* right = array + arraySize - 1;
	// Find first element from left that is greater than pivot and first element from right that is less than pivot and swap them
	while (left <= right)
	{
		++stats.steps;
		while (*left < pivot)
		{
			++stats.steps;
			++left;
		}
		while (*right > pivot)
		{
			++stats.steps;
			--right;
		}
		if (left <= right)
		{
			int temp = *left;
			*left = *right;
			*right = temp;
			++left;
			--right;
		}
	}

	// Sort left and right parts
	QuickSort(array, int(right - array + 1), stats);
	QuickSort(left, int(arraySize - (left - array)), stats);

	// Count variables on stack
	stats.memory += 4 * sizeof(int);
}


void MergeSort(int array[], int arraySize, Stats& stats)
{
	stats.dataLength = arraySize;
	++stats.steps;

	if (arraySize <= 1)
	{
		return;
	}

	// Sort left and right halves recursively
	int middle = arraySize / 2;
	MergeSort(array, middle, stats);
	MergeSort(array + middle, arraySize - middle, stats);

	// Merge sorted halves by saving it into additional array and then copying it back to original array
	int* temp = new int[arraySize];
	int left = 0;
	int right = middle;

	for (int i = 0; i < arraySize; ++i)
	{
		++stats.steps;
		if (right < arraySize && (left >= middle || array[right] < array[left]))
		{
			temp[i] = array[right];
			++right;
		}
		else
		{
			temp[i] = array[left];
			++left;
		}
	}

	for (int i = 0; i < arraySize; ++i)
	{
		++stats.steps;
		array[i] = temp[i];
	}

	delete[] temp;

	// Count variables on stack and temp array
	stats.memory += arraySize * sizeof(int) + 4 * sizeof(int);
}

void RandomizeArray(int array[], int arraySize)
{
	for (int i = 0; i < arraySize; ++i)
	{
		array[i] = rand() % 100;
	}
}

void CalculateSortStats()
{
	MultiStats<3> stats;
	stats.statNames[0] = "Bubble sort";
	stats.statNames[1] = "Quick sort";
	stats.statNames[2] = "Merge sort";

	const int arraySize = 1000;
	int array[arraySize];

	stats.stats.resize(arraySize);

	std::cout << "Calculating sort stats for array sizez up to " << arraySize << std::endl;

	for (int actualSize = 1; actualSize <= arraySize; ++actualSize)
	{
		auto& currentStats = stats.stats[actualSize - 1];
		InitStats(currentStats[0]);
		RandomizeArray(array, actualSize);
		BubbleSort(array, actualSize, currentStats[0]);

		InitStats(currentStats[1]);
		RandomizeArray(array, actualSize);
		QuickSort(array, actualSize, currentStats[1]);

		InitStats(currentStats[2]);
		RandomizeArray(array, actualSize);
		MergeSort(array, actualSize, currentStats[2]);
	}

	WriteMultipleStatsCSV("SortStats.csv", stats);
	std::cout << "Sort stats calculated and saved to SortStats.csv" << std::endl;
	std::cout << std::endl;
}

void LearnSorts()
{
	CalculateSortStats();
}

