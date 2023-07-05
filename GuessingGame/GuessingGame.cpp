// GuessingGame.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>

int main()
{
    // Initialize random seed
    srand((unsigned)time(nullptr));

	while (true)
	{
		int secretNumber = rand() % 101 + 1;
		std::cout << "'I've thought of a number between 1 and 100. How fast can you guess it?\n";

		bool isGuessed = false;
		int playerAmountOfTries = 0;
		while (!isGuessed)
		{
			std::cout << "Your try: ";
			++playerAmountOfTries;
			int guess = 0;
			std::cin >> guess;
			if (guess < secretNumber)
			{
				std::cout << "Too low!\n";
			}
			else if (guess > secretNumber)
			{
				std::cout << "Too high!\n";
			}
			else
			{
				std::cout << "You guessed it!\n";
				isGuessed = true;
			}
		}

		std::cout << "You guessed it in " << playerAmountOfTries << " tries!\n";
		if (playerAmountOfTries > 10)
		{
			std::cout << "You are not very good at this, are you?\n";
		}
		else if (playerAmountOfTries > 8)
		{
			std::cout << "Not bad, but you can do better!\n";
		}
		else if (playerAmountOfTries > 1)
		{
			std::cout << "You know the trick!\n";
		}
		else
		{
			std::cout << "You're lucky thing!\n";
		}

		// Pseudo code for computer guessing:
		// Init computers turn
		// Init min and max as 1 and 100
		// While not guessed or computer detected cheating
		//   increase tries counter
		//   take middle between min and max
		//   ask player if it is guessed
		//   if player said yes
		//       exit cycle
		//   else
		//     ask player if it is too low
		//     if player said yes
		//	     set min to guess + 1
		//     else
		//       set max to guess - 1
		//	
		//     if min >= max
		//		     say player "You are cheating!" and exit cycle
		// 
		// if computer tries less than player tries
		//   say "I won!"
		// else if computer tries more than player tries
		//   say "You won!"
		// else
		//   say "It's a draw!"


		std::cout << "Okay, now my turn! Think about some number from 1 to 100\n";
		isGuessed = false;
		int computerAmountOfTries = 0;
		int min = 1;
		int max = 100;
		while (!isGuessed)
		{
			++computerAmountOfTries;
			int guess = (min + max) / 2;
			std::cout << "My try: " << guess << "\n";
			std::cout << "Is it correct? (y/n)\n";
			std::string answer;
			std::cin >> answer;
			if (answer == "y")
			{
				std::cout << "I guessed it in " << computerAmountOfTries << " tries!\n";
				isGuessed = true;
			}
			else
			{
				std::cout << "Is it too low? (y/n)\n";
				std::cin >> answer;
				if (answer == "y")
				{
					min = guess + 1;
				}
				else
				{
					max = guess - 1;
				}

				if (min >= max)
				{
					std::cout << "You are cheating!\n";
					break;
				}
			}
		}

		if (computerAmountOfTries < playerAmountOfTries)
		{
			std::cout << "I won!\n";
		}
		else if (computerAmountOfTries > playerAmountOfTries)
		{
			std::cout << "You won!\n";
		}
		else
		{
			std::cout << "It's a draw!\n";
		}

		std::cout << "Do you want to play again? (y/n)\n";
		std::string answer;
		std::cin >> answer;
		if (answer != "y")
		{
			break;
		}
    }

	std::cout << "\n"
		<< R"(__     ______  _    _  ______  ______       __          ________  _____  ____   __  __ ______ )" << "\n"
		<< R"(\ \   / / __ \| |  | ()   __ \| ____|      /\ \        / /  ____|/ ____|/  __ \|  \/  | ____ |)" << "\n"
		<< R"( \ \_/ / |  | | |  | |/| |__) | |__       /  \ \  /\  / /| |__   | (___ | |  | | \  / | |__   )" << "\n"
		<< R"(  \   /| |  | | |  | | |  _  /|  __|     / /\ \ \/  \/ / |  __|   \__  \| |  | | |\/| |  __|  )" << "\n"
		<< R"(   | | | |__| | |__| | | | \ \| |____   / ____ \  /\  /  | |____ ____)  | |__| | |  | | |____ )" << "\n"
		<< R"(   |_|  \____/ \____/  |_|  \_\______| /_ /   \_\/  \/   |______|_____ /\_____/|_|  |_| _____|)" << "\n";
}
