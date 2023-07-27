#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Apple.h"
#include "UI.h"
#include "GameSettings.h"

namespace ApplesGame
{
	enum class GameOptions: std::uint8_t
	{
		InfiniteApples = 1 << 0,
		WithAcceleration = 1 << 1,

		Default = InfiniteApples | WithAcceleration,
		Empty = 0
	};

	struct GameState
	{
		GameOptions options = GameOptions::Default;
		Player player;
		Apple* apples = nullptr;
		int numApples = 0;
		int numEatenApples = 0;
		UIState uiState;
		bool isGameOver = false;
		float timeSinceGameOver = 0.f;

		// Game resources
		sf::Font font;
		sf::Texture playerTexture;
		sf::Texture appleTexture;
	};

	void InitGame(GameState& gameState);
	void RestartGame(GameState& gameState);
	void HandleWindowEvents(GameState& gameState, sf::RenderWindow& window);
	void UpdateGame(GameState& gameState, float timeDelta);
	void DrawGame(GameState& gameState, sf::RenderWindow& window);
	void ShutdownGame(GameState& gameState);
}
