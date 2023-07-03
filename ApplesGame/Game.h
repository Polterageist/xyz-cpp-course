#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Apple.h"
#include "GameSettings.h"

namespace ApplesGame
{
	struct GameState
	{
		Player player;
		Apple apples[NUM_APPLES];
		int numEatenApples = 0;
		bool isGameOver = false;

		// Game resources
		sf::Font font;
	};

	void InitGame(GameState& gameState);
	void HandleInput(GameState& gameState);
	void UpdateGame(GameState& gameState, float timeDelta);
	void DrawGame(GameState& gameState, sf::RenderWindow& window);
}
