#include "Game.h"
#include <assert.h>


namespace ApplesGame
{
	void InitGame(GameState& gameState)
	{
		// Init game resources (terminate if error)
		assert(gameState.playerTexture.loadFromFile(RESOURCES_PATH + "Pacman.png"));
		assert(gameState.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
		assert(gameState.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		// Init player
		InitPlayer(gameState.player, gameState.playerTexture);
		// Init apples
		for (int i = 0; i < NUM_APPLES; i++)
		{
			InitApple(gameState.apples[i], gameState.appleTexture);
		}

		// Init game state
		gameState.numEatenApples = 0;
		gameState.isGameOver = false;
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
		// Update player
		UpdatePlayer(gameState.player, timeDelta);

		// Check collision with screen border
		if (HasPlayerCollisionWithScreenBorder(gameState.player))
		{
			gameState.isGameOver = true;
			return;
		}

		for (int i = 0; i < NUM_APPLES; i++)
		{
			// Check collision with apple
			if (HasPlayerCollisionWithApple(gameState.player, gameState.apples[i]))
			{
				// Move apple to a new random position
				InitApple(gameState.apples[i], gameState.appleTexture);
				// Increase eaten apples counter
				gameState.numEatenApples++;
				// Increase player speed
				gameState.player.speed += ACCELERATION;
			}
		}
	}

	void DrawGame(GameState& gameState, sf::RenderWindow& window)
	{
		// Draw player
		DrawPlayer(gameState.player, window);
		// Draw apples
		for (int i = 0; i < NUM_APPLES; i++)
		{
			DrawApple(gameState.apples[i], window);
		}

		sf::Text scoresText;
		scoresText.setFont(gameState.font);
		scoresText.setString("Apples eaten: " + std::to_string(gameState.numEatenApples));
		scoresText.setCharacterSize(24);
		scoresText.setFillColor(sf::Color::Yellow);
		scoresText.setPosition(10.f, 10.f);
		window.draw(scoresText);
	}
}
