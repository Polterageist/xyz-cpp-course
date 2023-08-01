#include "Game.h"
#include <assert.h>
#include <algorithm>

namespace ApplesGame
{
	bool operator<(const RecordsTableItem& lhs, const RecordsTableItem& rhs)
	{
		return lhs.score > rhs.score;
	}

	void InitGame(GameState& gameState)
	{
		// Init game resources (terminate if error)
		assert(gameState.playerTexture.loadFromFile(RESOURCES_PATH + "Pacman.png"));
		assert(gameState.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
		assert(gameState.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		// Generate fake records table
		gameState.recordsTable[0] = { "John", 50 };
		gameState.recordsTable[1] = { "Alice", 40 };
		gameState.recordsTable[2] = { "Bob", 30 };
		gameState.recordsTable[3] = { "Clementine", 20 };
		gameState.recordsTable[4] = { "You", 0 };

		InitUI(gameState.uiState, gameState.font);
		RestartGame(gameState);
	}

	void RestartGame(GameState& gameState)
	{
		if (gameState.apples)
		{
			delete[] gameState.apples;

			gameState.apples = nullptr;
			gameState.numApples = 0;
		}
		
		// Init player
		InitPlayer(gameState.player, gameState.playerTexture);
		// Init apples
		gameState.numApples = MIN_APPLES + rand() % (MAX_APPLES + 1 - MIN_APPLES);
		gameState.apples = new Apple[gameState.numApples];
		for (int i = 0; i < gameState.numApples; i++)
		{
			InitApple(gameState.apples[i], gameState.appleTexture);
		}

		// Init game state
		gameState.numEatenApples = 0;
		gameState.isGameOver = false;
		gameState.timeSinceGameOver = 0.f;
	}

	void HandleWindowEvents(GameState& gameState, sf::RenderWindow& window)
	{
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

			if (gameState.isGameOver && (event.type == sf::Event::KeyPressed))
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					RestartGame(gameState);
				}
				else if (event.key.code == sf::Keyboard::Num1)
				{
					gameState.options = (GameOptions)((std::uint8_t)gameState.options ^ (std::uint8_t)GameOptions::InfiniteApples);
				}
				else if (event.key.code == sf::Keyboard::Num2)
				{
					gameState.options = (GameOptions)((std::uint8_t)gameState.options ^ (std::uint8_t)GameOptions::WithAcceleration);
				}

				// We don't handle input in game over state
				return;
			}

		}
	}

	void HandleInput(GameState& gameState)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			gameState.player.direction = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			gameState.player.direction = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			gameState.player.direction = PlayerDirection::Down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			gameState.player.direction = PlayerDirection::Left;
		}
	}

	void UpdateGame(GameState& gameState, float timeDelta)
	{
		if (!gameState.isGameOver)
		{
			HandleInput(gameState);

			// Update player
			UpdatePlayer(gameState.player, timeDelta);

			for (int i = 0; i < gameState.numApples; i++)
			{
				if (gameState.apples[i].isEaten)
				{
					continue;
				}

				// Check collision with apple
				if (HasPlayerCollisionWithApple(gameState.player, gameState.apples[i]))
				{
					if ((std::uint8_t)gameState.options & (std::uint8_t)GameOptions::InfiniteApples)
					{
						// Move apple to a new random position
						InitApple(gameState.apples[i], gameState.appleTexture);
					}
					else
					{
						// Mark apple as eaten
						gameState.apples[i].isEaten = true;
					}

					// Increase eaten apples counter
					gameState.numEatenApples++;
					// Increase player speed
					if ((std::uint8_t)gameState.options & (std::uint8_t)GameOptions::WithAcceleration)
					{
						gameState.player.speed += ACCELERATION;
					}
				}
			}

			bool isGameFinished = (gameState.numEatenApples == gameState.numApples) 
				&& !((std::uint8_t)gameState.options & (std::uint8_t)GameOptions::InfiniteApples);
			// Check collision with screen border
			if (isGameFinished || HasPlayerCollisionWithScreenBorder(gameState.player))
			{
				gameState.isGameOver = true;
				gameState.timeSinceGameOver = 0.f;

				// Find player in records table and update his score
				for (RecordsTableItem& item : gameState.recordsTable)
				{
					if (item.name == "You")
					{
						item.score = gameState.numEatenApples;
						break;
					}
				}

				// Sort records table
				std::sort(std::begin(gameState.recordsTable), std::end(gameState.recordsTable));
			}
		}
		else
		{
			gameState.timeSinceGameOver += timeDelta;
		}

		UpdateUI(gameState.uiState, gameState, timeDelta);
	}

	void DrawGame(GameState& gameState, sf::RenderWindow& window)
	{
		// Draw player
		DrawPlayer(gameState.player, window);
		// Draw apples
		for (int i = 0; i < gameState.numApples; i++)
		{
			DrawApple(gameState.apples[i], window);
		}

		DrawUI(gameState.uiState, window);
	}

	void ShutdownGame(GameState& gameState)
	{
		if (gameState.apples)
		{
			delete[] gameState.apples;
			gameState.apples = nullptr;
			gameState.numApples = 0;
		}
	}

}
