#include <iostream>
#include <bitset>


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


int main()
{
	learnLiteralsAndOutput();
	learnBitwiseOperations();
	learnBitfields();
}
