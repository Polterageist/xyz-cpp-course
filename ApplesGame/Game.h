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

	enum class GameState
	{
		None = 0,
		Playing,
		GameOver,
	};

	struct Game
	{
		GameOptions options = GameOptions::Default;
		Player player;
		std::vector<Apple> apples;
		ApplesGrid applesGrid;

		int numEatenApples = 0;
		UIState uiState;
		std::vector<GameState> gameStateStack;

		float timeSinceGameOver = 0.f;
		RecordsTableItem recordsTable[MAX_RECORDS_TABLE_SIZE];

		// Game resources
		sf::Font font;
		sf::Texture playerTexture;
		sf::Texture appleTexture;
	};

	void HandleWindowEvents(Game& game, sf::RenderWindow& window);
	void InitGame(Game& game);
	void UpdateGame(Game& game, float timeDelta);
	void RestartGame(Game& game);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void ShutdownGame(Game& game);

	void PushGameState(Game& game, GameState state);
	void PopGameState(Game& game);
	void SwitchGameState(Game& game, GameState newState);
	void SwitchGameStateInternal(Game& game, GameState oldState, GameState newState);
	GameState GetCurrentGameState(const Game& game);

	void InitPlayingState(Game& game);
	void UpdatePlayingState(Game& game, float timeDelta);
	void ShutdownPlayingState(Game& game);

	void InitGameOverState(Game& game);
	void UpdateGameOverState(Game& game, float timeDelta);
	void ShutdownGameOverState(Game& game);

	
}
