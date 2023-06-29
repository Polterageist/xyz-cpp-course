// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>

const std::string RESOURCES_PATH = "Resources/";

int main()
{
	unsigned int screenWidth = 800;
	unsigned int screenHeight = 600;
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "AppleGame");

	// Start in screen center
	float playerX = (float)screenWidth / 2.f;
	float playerY = (float)screenHeight / 2.f;
	float playerSize = 20.f;
	float playerSpeed = 100.f; // Pixels per second
	int playerDirection = 0; // 0 - up, 1 - right, 2 - down, 3 - left

	// Init player representation
	sf::RectangleShape playerShape(sf::Vector2f(playerSize, playerSize));
	playerShape.setFillColor(sf::Color::Green);
	playerShape.setOrigin(playerSize / 2.f, playerSize / 2.f);
	playerShape.setPosition(playerX, playerY);

	// Init game clock
	sf::Clock game_clock;
	sf::Time lastTime = game_clock.getElapsedTime();

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

		// Check collision with screen borders
		if (playerX < 0)
		{
			break;
		}
		else if (playerX > screenWidth)
		{
			break;
		}
		
		if (playerY < 0)
		{
			break;
		}
		else if (playerY > screenHeight)
		{
			break;
		}

		// Draw everything here
		window.clear();
		playerShape.setPosition(playerX, playerY);
		window.draw(playerShape);
		window.display();
	}

	return 0;
}
