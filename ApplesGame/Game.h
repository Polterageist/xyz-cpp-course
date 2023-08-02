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

	struct RecordsTableItem
	{
		std::string name;
		int score = 0;
	};

	bool operator<(const RecordsTableItem& lhs, const RecordsTableItem& rhs);

	struct GameState
	{
		GameOptions options = GameOptions::Default;
		Player player;
		std::vector<Apple> apples;
		ApplesGrid applesGrid;

		int numEatenApples = 0;
		UIState uiState;
		bool isGameOver = false;
		float timeSinceGameOver = 0.f;
		RecordsTableItem recordsTable[MAX_RECORDS_TABLE_SIZE];

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
