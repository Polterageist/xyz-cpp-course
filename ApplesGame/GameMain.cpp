// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <cstdlib>

#include "Game.h"

using namespace ApplesGame;

int main()
{
	// Init random number generator
	unsigned int seed = (unsigned int)time(nullptr); // Get current time as seed. You can also use any other number to fix randomization
	srand(seed);

	// Init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEGHT), "AppleGame");

	// We now use too much memory for stack, so we need to allocate it on heap
	ApplesGame::GameState* gameState = new ApplesGame::GameState();
	InitGame(*gameState);

	// Init game clock
	sf::Clock game_clock;
	sf::Time lastTime = game_clock.getElapsedTime();

	// Game loop
	while (window.isOpen())
	{
		HandleWindowEvents(*gameState, window);

		if (!window.isOpen())
		{
			break;
		}

		// Calculate time delta
		sf::Time currentTime = game_clock.getElapsedTime();
		float timeDelta = currentTime.asSeconds() - lastTime.asSeconds();
		lastTime = currentTime;
		UpdateGame(*gameState, timeDelta);

		// Draw everything here
		// Clear the window first
		window.clear();

		DrawGame(*gameState, window);

		// End the current frame, display window contents on screen
		window.display();
	}

	ShutdownGame(*gameState);
	delete gameState;
	gameState = nullptr;

	return 0;
}
