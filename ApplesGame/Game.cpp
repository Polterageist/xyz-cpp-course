#include "Game.h"

namespace ApplesGame
{
	void InitGame(GameState& gameState)
	{
		// Init player
		InitPlayer(gameState.player);
		// Init apples
		for (int i = 0; i < NUM_APPLES; i++)
		{
			InitApple(gameState.apples[i]);
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
				InitApple(gameState.apples[i]);
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
		window.draw(gameState.player.shape);
		// Draw apples
		for (int i = 0; i < NUM_APPLES; i++)
		{
			window.draw(gameState.apples[i].shape);
		}
	}
}
