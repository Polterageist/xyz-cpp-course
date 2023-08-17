#include "Templates.h"

// This list can work with any type
template<typename T>
struct List
{
	struct ListNode
	{
		T value;
		ListNode* prev = nullptr;
		ListNode* next = nullptr;
	};

	ListNode* first = nullptr;
	ListNode* last = nullptr;
};

// This function can work with any list
template<typename T>
void AddToList(List<T>& list, const T& value)
{
	std::cout << "Adding value of type " << typeid(T).name() << std::endl;
}

// This is specialization for the list of pointers
template<typename T>
void AddToList(List<T*>& list, T* const& value)
{
	std::cout << "Adding ptr to value of type " << typeid(T).name();
}

// List<int> now can be used as IntList
using IntList = List<int>;

// Another form of type definition
typedef List<float> FloatList;

// Using can itself be template
template<typename T>
using PtrList = List<T*>;

template<class T>
void TemplateFoo(T arg)
{
	std::cout << "You can't use me in other cpp" << std::endl;
}


// You can use simple types as template arguments
template<typename T, unsigned Num>
struct StaticArray
{
	static_assert(Num > 0, "Zero-sized arrays are not allowed");

	using iterator = T*;

	// This idiom is used to get size of array
	enum { Size = Num };

	T values[Num];

	// TODO array methods
};

// This is specialization for bool type, which uses memory effectively. Don
template<unsigned Num>
struct StaticArray<bool, Num>
{
	static_assert(Num > 0, "Zero-sized arrays are not allowed");
	using iterator = bool*;
	enum { Size = Num };
	// This is a specialization for bool type
	// We can't use bool array, as it will be packed into bytes
	// So we use char array instead
	char values[(Num + 7) / 8];

	// TODO array methods
};

// Specializtion for std::begin and std::end to allow range-based for loop
namespace std
{
	template<typename T, unsigned Num>
	T* begin(StaticArray<T, Num>& arr)
	{
		return arr.values;
	}

	template<typename T, unsigned Num>
	T* end(StaticArray<T, Num>& arr)
	{
		return arr.values + Num;
	}
}


void LearnTemplates()
{
	std::cout << "Learn templates" << std::endl;
	List<bool> boolList;
	AddToList(boolList, true);

	IntList intList;
	AddToList(intList, 3);

	FloatList floatList;
	AddToList(floatList, 3.f);

	// Error
	// AddToList(floatList, true);

	PtrList<int> intPtrList;
	int myval = 454;
	AddToList(intPtrList, &myval);

	StaticArray<int, 10> ints;

	// Range-based for works
	for (int& value : ints)
	{
		value = rand() % 100;
	}

	// Explicit type of iterator
	StaticArray<int, 10>::iterator it1 = std::begin(ints);
	// Simplified version with auto keyword
	auto it2 = std::begin(ints);

	// How to get the size of array
	unsigned arraySize = ints.Size;
	unsigned arraySize2 = StaticArray<int, 10>::Size;

	// Error
	// StaticArray<int, 0> error;

	std::cout << std::endl;
}
