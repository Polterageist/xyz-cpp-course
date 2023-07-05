#include <iostream>

int main()
{
    int box1 = 0;
    int box2 = 4;
    int box3 = 5;
    std::cout << "Apples in box1: " << box1 << "\n";
    std::cout << "Apples in box2: " << box2 << "\n";
    std::cout << "Apples in box3: " << box3 << "\n";

    int totalApples = box1 + box2 + box3;
    std::cout << "Total apples: " << totalApples << "\n";

    int average = totalApples / 3;
    std::cout << "Average apples: " << box3 << "\n";

    std::cout << "Distribute apples between boxes\n";

    std::cout << "How much apples to move from box3 to box1?\n";
    int applesToMove = 0;
    std::cin >> applesToMove;
    box1 += applesToMove;
    box3 -= applesToMove;

	std::cout << "Apples in box1: " << box1 << "\n";
	std::cout << "Apples in box2: " << box2 << "\n";
	std::cout << "Apples in box3: " << box3 << "\n";

    // Student exercise: move apples from box2 to box1
	//std::cout << "How much apples to move from box2 to box1?\n";
	//applesToMove = 0;
	//std::cin >> applesToMove;
	//box1 += applesToMove;
	//box2 -= applesToMove;

	std::cout << "Apples in box1: " << box1 << "\n";
	std::cout << "Apples in box2: " << box2 << "\n";
	std::cout << "Apples in box3: " << box3 << "\n";
}
