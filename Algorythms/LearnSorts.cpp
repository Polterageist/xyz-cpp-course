#include "LearnSorts.h"
#include "LearnAssymptoticAnalysis.h"
#include "Stats.h"
#include <iostream>
#include <algorithm>

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

struct PersonData
{
	std::string name;
	int age = 0;
};

// Operator < is required for std::sort
bool operator<(const PersonData& left, const PersonData& right)
{
	return left.age < right.age;
}

void LearnStdSorts()
{
	std::cout << "Learn std sorts" << std::endl;

	{
		std::cout << "Initial array:" << std::endl;
		PersonData people[] = { {"Alex", 23}, {"Alice", 10}, {"Bob", 23}, {"Clementine", 26}, {"Kate", 15}, {"Jack", 23}, {"Zack", 10} };
		for (const auto& person : people)
		{
			std::cout << person.name << " " << person.age << std::endl;
		}

		std::cout << "std::sort:" << std::endl;
		std::sort(std::begin(people), std::end(people));
		for (const auto& person : people)
		{
			std::cout << person.name << " " << person.age << std::endl;
		}
	}
	
	{
		PersonData people[] = { {"Alex", 23}, {"Alice", 10}, {"Bob", 23}, {"Clementine", 26}, {"Kate", 15}, {"Jack", 23}, {"Zack", 10} };

		std::cout << "std::stable_sort:" << std::endl;
		std::stable_sort(std::begin(people), std::end(people));
		for (const auto& person : people)
		{
			std::cout << person.name << " " << person.age << std::endl;
		}
	}
	
	std::cout << std::endl;
}

void RadixSort(std::string array[], int arraySize, Stats& stats)
{
	char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	const int alphabetSize = sizeof(alphabet);
	InitStats(stats);
	stats.dataLength = arraySize;

	// Find max string length
	int maxLength = 0;
	for (int i = 0; i < arraySize; ++i)
	{
		++stats.steps;
		if (array[i].length() > maxLength)
		{
			maxLength = (int)array[i].length();
		}
	}

	// Sort by each character from the end
	for (int i = maxLength - 1; i >= 0; --i)
	{
		// Counting sort
		int count[alphabetSize] = {0};
		for (int j = 0; j < arraySize; ++j)
		{
			++stats.steps;
			if (i < array[j].length())
			{
				++count[array[j][i] - alphabet[0]];
			}
			else
			{
				++count[alphabetSize - 1];
			}
		}
		for (int j = 1; j < alphabetSize; ++j)
		{
			++stats.steps;
			count[j] += count[j - 1];
		}
		std::string* temp = new std::string[arraySize];
		for (int j = arraySize - 1; j >= 0; --j)
		{
			++stats.steps;
			int index = 0;
			if (i < array[j].length())
			{
				index = array[j][i] - alphabet[0];
			}
			else
			{
				index = alphabetSize - 1;
			}
			temp[--count[index]] = array[j];
		}
		for (int j = 0; j < arraySize; ++j)
		{
			++stats.steps;
			array[j] = temp[j];
		}
		delete[] temp;
	}

	// Count variables on stack and temp array
	stats.memory += arraySize * sizeof(std::string) + alphabetSize * sizeof(int);
}

void RandomizeArray(std::string array[], int arraySize, int stringLength)
{
	for (int i = 0; i < arraySize; ++i)
	{
		std::string& string = array[i];
		string.clear();
		for (int j = 0; j < stringLength; ++j)
		{
			string += rand() % 26 + 'a';
		}
	}
}

void CalculateRadixSort()
{
	MultiStats<1> stats;
	stats.statNames[0] = "Radix sort";
	const int arraySize = 100;
	const int stringLength = 10;
	std::string array[arraySize];
	stats.stats.resize(arraySize);
	std::cout << "Calculating radix sort stats for array sizes up to " << arraySize << std::endl;
	for (int actualSize = 1; actualSize <= arraySize; ++actualSize)
	{
		auto& currentStats = stats.stats[actualSize - 1];
		InitStats(currentStats[0]);
		RandomizeArray(array, actualSize, stringLength);
		RadixSort(array, actualSize, currentStats[0]);
	}
	WriteMultipleStatsCSV("RadixSortStats.csv", stats);
	std::cout << "Radix sort stats calculated and saved to RadixSortStats.csv" << std::endl;
	std::cout << std::endl;
}

void LearnSorts()
{
	CalculateSortStats();
	LearnStdSorts();
	CalculateRadixSort();
}
