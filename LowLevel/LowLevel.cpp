#include <iostream>
#include <bitset>
#include <typeinfo>
#include <iomanip>


void learnLiteralsAndOutput()
{
	std::cout << "Literals and output\n";

	// Decimal literal
	int num = 34;
	std::cout << "num = " << num << "\n";
	// Output in binary
	std::cout << "(bin) num = 0b" << std::bitset<32>(num) << "\n";
	// Output in octal
	std::cout << "(oct) num = 0" << std::oct << num << "\n";
	// Output in hex
	std::cout << "(hex) num = 0x" << std::hex << num << "\n";

	// Binary literal
	int num2 = 0b00100010;
	std::cout << "0b00100010 = " << std::dec << num2 << "\n";

	// Octal literal
	num2 = 042;
	std::cout << "042 = " << std::dec << num2 << "\n";

	// Hex literal
	num2 = 0x22;
	std::cout << "0x22 = " << std::dec << num << "\n";

	std::cout << "\n";
}


void learnBitwiseOperations()
{
	std::cout << "Bitwise operations\n";

	// Bitwise operations
	std::bitset<8> a = 0b00100010;
	std::bitset<8> b = 0b00001111;

	// Bitwise AND
	std::bitset<8> c = a & b; // 0b00000010
	std::cout << "a & b = " << c << "\n";

	// Bitwise OR
	c = a | b; // 0b00101111
	std::cout << "a | b = " << c << "\n";

	// Bitwise XOR
	c = a ^ b; // 0b00101101
	std::cout << "a ^ b = " << c << "\n";

	// Bitwise NOT
	c = ~a; // 0b11011101
	std::cout << "~a = " << c << "\n";

	// Bitwise shift left
	c = a << 2; // 0b10001000
	std::cout << "a << 2 = " << c << "\n";

	// Bitwise shift right
	c = a >> 2; // 0b00001000
	std::cout << "a >> 2 = " << c << "\n";

	std::cout << "\n";
}


enum class WindowMode
{
	Windowed = 0x01,
	FullScreen = 0x02,
	Borderless = 0x04,
	Color32Bit = 0x10,
	Resizable = 0x20,

	// BitField combination
	Default = FullScreen | Borderless | Color32Bit,
	NoOptions = 0x00
};

void printWindowMode(WindowMode mode)
{
	std::cout << "WindowMode = " << std::bitset<8>((int)mode) << "\n";
}

void learnBitfields()
{
	std::cout << "Bit fields\n";

	WindowMode options = WindowMode::Default;
	printWindowMode(options);

	// Check which options are enabled
	bool bIsWindowed = ((int)options & (int)WindowMode::Windowed) == (int)WindowMode::Windowed;
	bool bIsFullScreen = ((int)options & (int)WindowMode::FullScreen) == (int)WindowMode::FullScreen;

	// Disable Color32Bit
	WindowMode options2 = (WindowMode)((int)WindowMode::Default & ~(int)WindowMode::Color32Bit);
	printWindowMode(options2);

	std::cout << "\n";
}


// Helper function to print type name and hex representation of a number
template<typename T>
void printBin(T srtct)
{
	const std::uint8_t* bytes = (const uint8_t*)&srtct;
	std::cout << typeid(T).name() << "(size = " << sizeof(srtct) << ", bin = 0b";
	for (int i = 0; i < sizeof(T); ++i)
	{
		std::cout << std::bitset<8>(bytes[i]);
	}
	std::cout << ")\n";
}

void learnInts()
{
	std::cout << "Integers\n";

	// Signed int
	int intNum = -3432;
	printBin(intNum);

	// int overflow
	int intNum2 = std::numeric_limits<int>::max();
	printBin(intNum2);
	intNum2 += 1;
	printBin(intNum2);

	// short
	short shortNum = 532;
	printBin(shortNum);

	// long
	long longNum = 3454;
	printBin(longNum);

	// long long
	long long longLongNum = 533454635;
	printBin(longLongNum);

	// char
	char charNum = 54;
	printBin(charNum);

	// int8_t
	std::int8_t int8num = 127;
	printBin(int8num);

	// int16_t
	std::int16_t int16num = 54;
	printBin(int16num);

	// int32_t
	std::int32_t int32num = 128;
	printBin(int32num);

	// int64_t
	std::int64_t int64num = 128;
	printBin(int64num);

	// unsigned int
	unsigned int uintNum = 3432u;
	printBin(uintNum);

	// unsigned overflow
	uintNum = 0u;
	uintNum -= 1u;
	printBin(uintNum);

	unsigned char ucharNum = 54u;
	printBin(ucharNum);

	// uint8_t
	std::uint8_t uint8num = 128;
	printBin(uint8num);

	// uint16_t
	std::uint16_t uint16num = 54;
	printBin(uint16num);

	// uint32_t
	std::uint32_t uint32num = 128;
	printBin(uint32num);

	// uint64_t
	std::uint64_t uint64num = 128;
	printBin(uint64num);

	std::cout << "\n";
}

void learnBools()
{
	std::cout << "Booleans\n";
	
	bool bTrue = true;
	bool bFalse = false;
	printBin(bTrue);
	printBin(bFalse);
	
	std::cout << "\n";
}

void learnFloats()
{
	std::cout << "Floats\n";
	
	float floatNum = 3.14f;
	printBin(floatNum);
	
	double doubleNum = 3.14;
	printBin(doubleNum);
	
	long double longDoubleNum = 3.14l;
	printBin(longDoubleNum);

	std::cout << "\n";
}

struct RGBA
{
	uint8_t R = 0;
	uint8_t G = 0;
	uint8_t B = 0;
	uint8_t A = 0;
};

struct RGB8
{
	uint8_t R : 3;
	uint8_t G : 3;
	uint8_t B : 2;
};

void learnStructs()
{
	std::cout << "Structs\n";
	RGBA rgba;
	rgba.R = 125;
	rgba.G = 45;
	rgba.B = 255;
	rgba.A = 128;
	printBin(rgba);

	RGB8 rgb8;
	rgb8.R = 0b001;
	rgb8.G = 0b100;
	rgb8.B = 0b11;
	printBin(rgb8);
	std::cout << "\n";
}

void learnArrays()
{
	std::cout << "Arrays\n";
	
	int intArray[5] = { 0, 1, 2, 3, 4 };
	printBin(intArray);
	
	// But the same code here will do another
	const std::uint8_t* bytes = (const uint8_t*)intArray;
	std::cout << typeid(intArray).name() << "(size = " << sizeof(intArray) << ", bin = 0b";
	for (int i = 0; i < sizeof(intArray); ++i)
	{
		std::cout << std::bitset<8>(bytes[i]);
	}

	std::cout << "\n";
}

struct MyStruct
{
	int a = 0;
	int b = 0;
	mutable int c = 0;
};

void learnCasts()
{
	std::cout << "Casts\n";

	const int constInt = 5;
	std::cout << "constInt=" << constInt << "\n";

	float floatNum = 3.14f;
	// int intNum = floatNum; // Warning
	int castedInt = static_cast<int>(floatNum); // No waarning
	std::cout << "castedInt=" << castedInt << "\n";

	// int& intRef = floatNum; // Error
	int& castedIntRef = reinterpret_cast<int&>(floatNum); // No error
	castedIntRef = 10;
	std::cout << "castedIntRef=" << castedIntRef << "\n";
	std::cout << "floatNum=" << floatNum << "\n";

	// C-style cast
	floatNum = 343;
	int& castedIntRef2 = (int&)floatNum;
	std::cout << "castedIntRef2=" << castedIntRef2 << "\n";
	int castedInt2 = (int)floatNum;
	std::cout << "castedInt2=" << castedInt2 << "\n";

	// Const casts
	const MyStruct some = { 1, 2, 3 };
	// some.a = 4; // Error
	std::cout << "some.a=" << some.a << "\n";
	const_cast<MyStruct&>(some).a = 5;
	std::cout << "some.a=" << some.a << "\n";
	// (yStruct&)(some).a = 454; // Error

	// Mutable members
	std::cout << "some.c=" << some.c << "\n";
	some.c = 6;
	std::cout << "some.c=" << some.c << "\n";

	std::cout << "\n";
}

void learnPointers()
{
	std::cout << "Pointers\n";

	// Difference between pointer and reference
	int var = 565;
	int* varPointer = &var;
	int& varRef = var;
	std::cout << "Var=" << var << "\n";
	std::cout << "Pointer=" << varPointer << ", Value=" << *varPointer << "\n";
	std::cout << "Ref=" << varRef << "\n";

	var = 453;
	std::cout << "Var=" << var << "\n";
	std::cout << "Pointer=" << varPointer << ", Value=" << *varPointer << "\n";
	std::cout << "Ref=" << varRef << "\n";

	int var2 = 353;
	varPointer = &var2;
	std::cout << "Var=" << var << "\n";
	std::cout << "Pointer=" << varPointer << ", Value=" << *varPointer << "\n";
	std::cout << "Ref=" << varRef << "\n";
	varRef = var2;
	std::cout << "Var=" << var << "\n";
	std::cout << "Pointer=" << varPointer << ", Value=" << *varPointer << "\n";
	std::cout << "Ref=" << varRef << "\n";

	varPointer = nullptr;
	std::cout << "Pointer=" << varPointer << "\n";

	// Will crash
	//std::cout << "*Pointer=" << *varPointer << "\n";

	varPointer = &var;
	int** pointerToPointer = &varPointer;
	std::cout << "pointerToPointer=" << pointerToPointer << ", Value=" << *pointerToPointer << "\n";
	std::cout << "**pointerToPointer=" << **pointerToPointer << "\n";

	std::cout << "\n";
}

void bufferOverflow(int array[])
{
	std::cout << "Buffer overflow\n";
	std::cout << "array[10]=" << array[10] << "\n";
	std::cout << "*(array + 10)=" << *(array + 10) << "\n";
}

void printArray(int array[], size_t size)
// void printArray(int* array, size_t size) // Equivalent
{
	std::cout << "array={";
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << array[i];
		if (i < size - 1)
		{
			std::cout << ", ";
		}
	}
	std::cout << "}\n";
}

void learnArraysAndPointers()
{
	std::cout << "Arrays and Pointers\n";

	// Array is pointer
	const size_t arraySize = 10;
	int array[arraySize] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	printArray(array, arraySize);

	int* pointer = array;
	std::cout << "array[2]=" << array[2] << "\n";
	std::cout << "pointer[2]=" << pointer[2] << "\n";

	// Address ariphemtics
	std::cout << "*(pointer + 2)=" << *(pointer + 2) << "\n";
	std::cout << "*(array + 2)=" << *(array + 2) << "\n";

	bufferOverflow(array);

	// Void pointers
	void* vPointer = (void*)pointer;

	// *vPointer is invalid
	// std::cout << "*vPointer=" << *vPointer << "\n";

	// cast to short
	short* shortPointer = (short*)(vPointer);
	std::cout << "*(shortPointer + 2)=" << *(shortPointer + 2) << "\n";
	std::cout << "*(shortPointer + 3)=" << *(shortPointer + 3) << "\n";
	std::cout << "*(shortPointer + 2 * sizeof(int))=" << *(shortPointer + 2 * sizeof(int)) << "\n";
	int* intPointer = (int*)(shortPointer + 2 * sizeof(int));
	std::cout << "*(intPointer)=" << *intPointer << "\n";

	*(array + 2) = 54;
	printArray(array, arraySize);

	std::cout << "\n";
}

int* getStackVar(int val)
{
	int var = val;
	return &var; // Produces warning
}

int* getHeapVar(int val)
{
	int* var = new int(val);
	return var;
}

void learnStackAndHeap()
{
	std::cout << "Stack and Heap\n";

	int* pointer = getStackVar(10);
	std::cout << "pointer=" << pointer << "\n";
	std::cout << "*pointer=" << *pointer << "\n"; // UB

	pointer = getHeapVar(20);
	std::cout << "pointer=" << pointer << "\n";
	std::cout << "*pointer=" << *pointer << "\n"; // UB

	// Avoid memory leaks
	delete pointer;

	std::cout << "\n";
}

void learnMemoryOps()
{
	std::cout << "Memory operations\n";
	// Memory operations
	const int arraySize = 10;
	int* array = (int*)malloc(arraySize * sizeof(int));
	// array = new int[arraySize]; // C++ equivalent
	if (array == nullptr)
	{
		std::cout << "Failed to allocate memory\n";
		return;
	}

	printArray(array, arraySize);

	// Set memory
	memset((void*)array, 0, arraySize * sizeof(int));
	printArray(array, arraySize);

	// Copy memory
	for (size_t i = 0; i < arraySize; ++i)
	{
		array[i] = (int)i;
	}
	printArray(array, arraySize);
	int array2[arraySize];
	memcpy((void*)array2, (void*)array, arraySize * sizeof(int));
	printArray(array2, arraySize);

	// Compare memory
	std::cout << "memcmp(array, array2, sizeof(array))=" << memcmp(array, array2, sizeof(array)) << "\n";
	array[0] = 1;
	std::cout << "memcmp(array, array2, sizeof(array))=" << memcmp(array, array2, sizeof(array)) << "\n";

	array[6] = 1;
	std::cout << "memcmp(array, array2, sizeof(array))=" << memcmp(array, array2, sizeof(array)) << "\n";

	// Free memory
	free(array);
	// delete[] array; // C++ equivalent
	array = nullptr; // Always set to nullptr after free, as ptr is invalid now

	std::cout << "\n";
}

struct DynArray
{
	int* data;
	size_t size;
};

DynArray* createDynArray(size_t size)
{
	DynArray* array = new DynArray();
	array->data = new int[size];
	array->size = size;
	return array;
}

void deleteDynArray(DynArray* array)
{
	delete[] array->data;
	delete array;
}

void addElement(DynArray* array, int element)
{
	int* newData = new int[array->size + 1];
	memcpy(newData, array->data, array->size * sizeof(int));
	newData[array->size] = element;
	delete[] array->data;
	array->data = newData;
	array->size += 1;
}

void removeElement(DynArray* array, size_t index)
{
	if (index >= array->size)
	{
		return;
	}
	int* newData = new int[array->size - 1];
	memcpy(newData, array->data, index * sizeof(int));
	memcpy(newData + index, array->data + index + 1, (array->size - index - 1) * sizeof(int));
	delete[] array->data;
	array->data = newData;
	array->size -= 1;
}

void learnDynArray()
{
	std::cout << "Dynamic array\n";
	DynArray* array = createDynArray(10);
	for (size_t i = 0; i < array->size; ++i)
	{
		array->data[i] = (int)i;
	}
	printArray(array->data, array->size);
	addElement(array, 10);
	printArray(array->data, array->size);
	removeElement(array, 5);
	printArray(array->data, array->size);
	deleteDynArray(array);
	std::cout << "\n";
}

int main()
{
	// Lesson 2
	learnLiteralsAndOutput();
	learnBitwiseOperations();
	learnBitfields();

	// Lesson 3
	learnInts();
	learnBools();
	learnFloats();
	learnStructs();
	learnArrays();
	learnCasts();

	// Lesson 4
	learnPointers();
	learnArraysAndPointers();
	learnStackAndHeap();
	learnMemoryOps();
	learnDynArray();
}
