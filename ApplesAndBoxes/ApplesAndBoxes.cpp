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

    if (applesToMove > box3)
    {
		std::cout << "Not enough apples in box3\n";
	}
    else if (applesToMove < 0)
    {
		std::cout << "Cannot move negative amount of apples\n";
	}
    else
    {
		box1 += applesToMove;
		box3 -= applesToMove;
    }

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

    std::cout << "Enter box index, from which you want to take apples: ";
    unsigned int sourceBoxIndex = 0;
    std::cin >> sourceBoxIndex;

    bool isInputValid = sourceBoxIndex >= 1 && sourceBoxIndex <= 3;
	// isInputValid = !(sourceBoxIndex < 1 || sourceBoxIndex > 3);

    if (!isInputValid)
    {
        std::cout << "Invalid box indexes\n";
        return 0;
    }

	int applesToTake = 0;
	std::cout << "How much apples to take? ";
	std::cin >> applesToMove;
	if (applesToTake >= 0)
	{
		switch (sourceBoxIndex)
		{
		case 1:
		{
			if (applesToTake < box1)
			{
				box1 -= applesToTake;
			}
			else
			{
				std::cout << "Not enough apples in box1\n";
			}
			break;
		}
		case 2:
		{
			if (applesToTake < box2)
			{
				box2 -= applesToTake;
			}
			else
			{
				std::cout << "Not enough apples in box2\n";
			}
			break;
		}
		case 3:
		{
			if (applesToTake < box3)
			{
				box3 -= applesToTake;
			}
			else
			{
				std::cout << "Not enough apples in box2\n";
			}
			break;
		}
		}
	}

	std::cout << "Apples in box1: " << box1 << "\n";
	std::cout << "Apples in box2: " << box2 << "\n";
	std::cout << "Apples in box3: " << box3 << "\n";
}
