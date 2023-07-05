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
		int amountOfTries = 0;
		while (!isGuessed)
		{
			std::cout << "Your try: ";
			++amountOfTries;
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

		std::cout << "You guessed it in " << amountOfTries << " tries!\n";
		if (amountOfTries > 10)
		{
			std::cout << "You are not very good at this, are you?\n";
		}
		else if (amountOfTries > 8)
		{
			std::cout << "Not bad, but you can do better!\n";
		}
		else if (amountOfTries > 1)
		{
			std::cout << "You know the trick!\n";
		}
		else
		{
			std::cout << "You're lucky thing!\n";
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
