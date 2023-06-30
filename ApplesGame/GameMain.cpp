// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <cstdlib>

const std::string RESOURCES_PATH = "Resources/";

const float PLAYER_SIZE = 20.f;
const float APPLE_SIZE = 20.f;
const float INITIAL_SPEED = 100.f;
const int NUM_APPLES = 20;

struct Apple
{
	float x = 0.f;
	float y = 0.f;
	sf::CircleShape shape;
};

int main()
{
	// Init random number generator
	unsigned int seed = (unsigned int)time(nullptr); // Get current time as seed. You can also use any other number to fix randomization
	srand(seed);

	// Init window
	unsigned int screenWidth = 800;
	unsigned int screenHeight = 600;
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "AppleGame");

	// Start in screen center
	float playerX = (float)screenWidth / 2.f;
	float playerY = (float)screenHeight / 2.f;
	
	float playerSpeed = INITIAL_SPEED; // Pixels per second
	float acceleration = 10.f; // For each eaten apple player speed will be increased by this value
	int playerDirection = 0; // 0 - up, 1 - right, 2 - down, 3 - left

	// Init player representation
	sf::RectangleShape playerShape(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	playerShape.setFillColor(sf::Color::Green);
	playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
	playerShape.setPosition(playerX, playerY);

	// Init apples
	Apple apples[NUM_APPLES];
	for (int i = 0; i < NUM_APPLES; i++)
	{
		apples[i].x = (float)(rand() % screenWidth);
		apples[i].y = (float)(rand() % screenHeight);
	}

	// Init apples representation (as circles)
	for (int i = 0; i < NUM_APPLES; i++)
	{
		apples[i].shape.setRadius(APPLE_SIZE / 2.f);
		apples[i].shape.setFillColor(sf::Color::Red);
		apples[i].shape.setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
		apples[i].shape.setPosition(apples[i].x, apples[i].y);
	}

	// Init game clock
	sf::Clock game_clock;
	sf::Time lastTime = game_clock.getElapsedTime();

	// Init eaten apples counter
	int numEatenApples = 0;

	// Game loop
	while (window.isOpen())
	{
		// Calculate time delta
		sf::Time currentTime = game_clock.getElapsedTime();
		float timeDelta = currentTime.asSeconds() - lastTime.asSeconds();
		lastTime = currentTime;

		// Handle window events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window if close button or Escape key pressed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
			{
				window.close();
			}
		}

		// Handle player input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			playerDirection = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			playerDirection = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			playerDirection = 2;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			playerDirection = 3;
		}

		// Move player
		if (playerDirection == 0)
		{
			playerY -= playerSpeed * timeDelta;
		}
		else if (playerDirection == 1)
		{
			playerX += playerSpeed * timeDelta;
		}
		else if (playerDirection == 2)
		{
			playerY += playerSpeed * timeDelta;
		}
		else if (playerDirection == 3)
		{
			playerX -= playerSpeed * timeDelta;
		}

		// Check collision with screen borders and determine if game should be restarted
		bool shouldRestartGame = 
			(playerX - PLAYER_SIZE / 2.f < 0) ||
			(playerX + PLAYER_SIZE / 2.f > screenWidth) ||
			(playerY - PLAYER_SIZE / 2.f < 0) ||
			(playerY + PLAYER_SIZE / 2.f > screenHeight);
		
		// Restart game if needed
		if (shouldRestartGame)
		{
			// Reset player position
			playerX = (float)screenWidth / 2.f;
			playerY = (float)screenHeight / 2.f;
			playerShape.setPosition(playerX, playerY);
			// Reset player speed and direction
			playerSpeed = INITIAL_SPEED;
			playerDirection = 0;
			// Reset eaten apples counter
			numEatenApples = 0;

			// Move apples to a new random positions
			for (int i = 0; i < NUM_APPLES; i++)
			{
				apples[i].x = (float)(rand() % screenWidth);
				apples[i].y = (float)(rand() % screenHeight);
			}
		}

		// Check collision with apples
		for (int i = 0; i < NUM_APPLES; i++)
		{
			// Calculate distance between player and apple by each axis (if apples are squares)
			/* float dx = fabs(playerX - AppleX[i]);
			float dy = fabs(playerY - AppleY[i]);
			if (dx < (PLAYER_SIZE + APPLE_SIZE) / 2.f &&
				dy < (PLAYER_SIZE + APPLE_SIZE) / 2.f)
			{
				// Increase player speed and eaten apples counter
				playerSpeed += acceleration;
				numEatenApples++;

				// Move apple to a new random position
				AppleX[i] = (float)(rand() % screenWidth);
				AppleY[i] = (float)(rand() % screenHeight);
			} */

			// Calculate distance between player and apple (if apples are circles)
			float dx = playerX - apples[i].x;
			float dy = playerY - apples[i].y;
			float distance = sqrt(dx * dx + dy * dy);
			if (distance < (PLAYER_SIZE + APPLE_SIZE) / 2.f)
			{
				// Increase player speed and eaten apples counter
				playerSpeed += acceleration;
				numEatenApples++;

				// Move apple to a new random position
				apples[i].x = (float)(rand() % screenWidth);
				apples[i].y = (float)(rand() % screenHeight);
			}
		}

		//// Check if all apples are eaten (win condition)
		//if (numEatenApples == NUM_APPLES)
		//{
		//	break;
		//}

		// Draw everything here
		// Clear the window first
		window.clear();

		// Then draw all the player
		playerShape.setPosition(playerX, playerY);
		window.draw(playerShape);

		// Then draw all the apples
		for (int i = 0; i < NUM_APPLES; i++)
		{
			apples[i].shape.setPosition(apples[i].x, apples[i].y);
			window.draw(apples[i].shape);
		}

		// End the current frame, display window contents on screen
		window.display();
	}

	return 0;
}
