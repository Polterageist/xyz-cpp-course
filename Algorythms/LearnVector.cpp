#include "LearnVector.h"
#include <vector>
#include <iostream>
#include <algorithm>

void PrintVector(std::vector<int>& v)
{
	std::cout << "Vector: [";
	for (int i = 0; i < v.size(); ++i)
	{
		std::cout << v[i];
		if (i < v.size() - 1)
		{
			std::cout << ", ";
		}
	}
	std::cout << "]\n";
}

// std::remove just moves elements to the position of removed elemnts and returns new iterator to the end
// so erase just cuts the tail of the vector without elements reposition
int* RemoveImplementation(int* begin, int* end, int elem)
{
	for (auto it = begin; it != end; ++it)
	{
		if (*it == elem)
		{
			*it = *(end - 1);
			--end;
		}
	}

	return end;
}

void LearnVector()
{
	std::cout << "Learn vector...\n";

	std::vector <int> v = { 1, 2, 3, 4, 5, 6};
	PrintVector(v);

	std::cout << "Another way of iterating...\n";
	for (int elem : v)
	{
		std::cout << elem << " ";
	}
	std::cout << "\n";

	std::cout << "And with iterators in reverse order...\n";
	for (std::vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << "\n";

	std::cout << "Add one more element to the end of vector...\n";
	v.push_back(7);
	PrintVector(v);

	std::cout << "Insert element 8 at index 2...\n";
	v.insert(v.begin() + 2, 8);
	PrintVector(v);

	std::cout << "Erase element at index 3...\n";
	v.erase(v.begin() + 3);
	PrintVector(v);

	std::cout << "Erase elements from index 2 to index 4...\n";
	v.erase(v.begin() + 2, v.begin() + 4);

	std::cout << "Clear vector...\n";
	v.clear();
	PrintVector(v);

	std::cout << "Generate vector with 20 elements with random values...\n";
	v.reserve(20); // Do it to optimize memory allocation
	std::cout << "Vector size:" << v.size() << ", Vector capacity: " << v.capacity() << std::endl;
	for (int i = 0; i < 20; ++i)
	{
		v.push_back(rand() % 100);
	}
	PrintVector(v);

	std::cout << "Sort vector...\n";
	std::sort(v.begin(), v.end());
	PrintVector(v);

	// Iterator and pointer can become invalid after insert operation, as memory could be reallocated
	std::cout << "Iterator may become invalid after erase operation" << std::endl;
	std::cout << "So, we need to use erase-remove idiom (and it is more optimal)" << std::endl;
	auto it = v.begin() + 10;
	std::cout << "Iterator value before erase: " << *it << std::endl;
	v.erase(std::remove(v.begin(), v.end(), 5), v.end());
	std::cout << "Iterator value after erase: " << *it << std::endl;
	PrintVector(v);

	std::vector<int> v2 = { 1, 2, 3, 4, 5, 6 };
	std::cout << "Swap vectors...\n";
	v.swap(v2); // It is effective as it just swaps pointers to data
	PrintVector(v);
}
