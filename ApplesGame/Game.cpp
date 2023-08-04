#include "Game.h"
#include <assert.h>
#include <algorithm>

namespace ApplesGame
{
	bool operator<(const RecordsTableItem& lhs, const RecordsTableItem& rhs)
	{
		return lhs.score > rhs.score;
	}

	void InitGame(Game& game)
	{
		// Init game resources (terminate if error)
		assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "Pacman.png"));
		assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
		assert(game.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		// Generate fake records table
		game.recordsTable[0] = { "John", MAX_APPLES };
		game.recordsTable[1] = { "Alice", MAX_APPLES / 2 };
		game.recordsTable[2] = { "Bob", MAX_APPLES / 3 };
		game.recordsTable[3] = { "Clementine", MAX_APPLES / 4 };
		game.recordsTable[4] = { "You", 0 };

		game.gameStateStack.push_back(GameState::Playing);

		InitUI(game.uiState, game.font);

		PushGameState(game, GameState::Playing);
	}

	void RestartGame(Game& game)
	{
		SwitchGameState(game, GameState::Playing);
	}

	void HandleWindowEvents(Game& game, sf::RenderWindow& window)
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

			if (GetCurrentGameState(game) == GameState::GameOver && (event.type == sf::Event::KeyPressed))
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					RestartGame(game);
				}
				else if (event.key.code == sf::Keyboard::Num1)
				{
					game.options = (GameOptions)((std::uint8_t)game.options ^ (std::uint8_t)GameOptions::InfiniteApples);
				}
				else if (event.key.code == sf::Keyboard::Num2)
				{
					game.options = (GameOptions)((std::uint8_t)game.options ^ (std::uint8_t)GameOptions::WithAcceleration);
				}

				// We don't handle input in game over state
				return;
			}

		}
	}

	void UpdateGame(Game& game, float timeDelta)
	{
		GameState gameState = game.gameStateStack.back();
		switch (gameState)
		{
		case ApplesGame::GameState::Playing:
			UpdatePlayingState(game, timeDelta);
			break;
		case ApplesGame::GameState::GameOver:
			UpdateGameOverState(game, timeDelta);
			break;
		default:
			break;
		}

		UpdateUI(game.uiState, game, timeDelta);
	}

	void PushGameState(Game& game, GameState state)
	{
		GameState oldState = GameState::None;
		if (game.gameStateStack.size() > 0)
		{
			oldState = game.gameStateStack.back();
		}

		SwitchGameStateInternal(game, oldState, state);
		game.gameStateStack.push_back(state);
	}

	void PopGameState(Game& game)
	{
		GameState oldState = GameState::None;
		if (game.gameStateStack.size() > 0)
		{
			oldState = game.gameStateStack.back();
		}

		game.gameStateStack.pop_back();
		GameState state = GameState::None;
		if (game.gameStateStack.size() > 0)
		{
			state = game.gameStateStack.back();
		}

		SwitchGameStateInternal(game, oldState, state);
	}

	void SwitchGameState(Game& game, GameState newState)
	{
		if (game.gameStateStack.size() > 0)
		{
			GameState oldState = game.gameStateStack.back();
			game.gameStateStack.pop_back();
			game.gameStateStack.push_back(newState);
			SwitchGameStateInternal(game, oldState, newState);
		}
		else
		{
			PushGameState(game, newState);
		}
	}

	void SwitchGameStateInternal(Game& game, GameState oldState, GameState newState)
	{
		switch (oldState)
		{
		case GameState::Playing:
		{
			ShutdownPlayingState(game);
			break;
		}
		case GameState::GameOver:
		{
			ShutdownGameOverState(game);
			break;
		}
		}

		switch (newState)
		{
		case ApplesGame::GameState::Playing:
			InitPlayingState(game);
			break;
		case ApplesGame::GameState::GameOver:
			InitGameOverState(game);
			break;
		default:
			break;
		}
	}

	GameState GetCurrentGameState(const Game& game)
	{
		if (game.gameStateStack.size() > 0)
		{
			return game.gameStateStack.back();
		}
		else
		{
			return GameState::None;
		}
	}

	void HandleInput(Game& game)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			game.player.direction = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			game.player.direction = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			game.player.direction = PlayerDirection::Down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			game.player.direction = PlayerDirection::Left;
		}
	}

	void InitPlayingState(Game& game)
	{
		game.apples.clear();

		// Init player
		InitPlayer(game.player, game.playerTexture);
		// Init apples
		ClearApplesGrid(game.applesGrid);
		int numApples = MIN_APPLES + rand() % (MAX_APPLES + 1 - MIN_APPLES);
		game.apples.resize(numApples);
		for (Apple& apple : game.apples)
		{
			InitApple(apple, game.appleTexture);
			ResetAppleState(apple);
			AddAppleToGrid(game.applesGrid, apple);
		}

		// Init game state
		game.numEatenApples = 0;
	}

	void UpdatePlayingState(Game& game, float timeDelta)
	{
		HandleInput(game);

		// Update player
		UpdatePlayer(game.player, timeDelta);

		Apple* collidingApples[MAX_APPLES_IN_CELL] = { nullptr };
		int numCollidingApples = 0;

		if (FindPlayerCollisionWithApples(game.player.position, game.applesGrid, collidingApples, numCollidingApples))
		{
			for (int i = 0; i < numCollidingApples; i++)
			{
				if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::InfiniteApples)
				{
					// Move apple to a new random position
					ResetAppleState(*collidingApples[i]);
					AddAppleToGrid(game.applesGrid, *collidingApples[i]);
				}
				else
				{
					// Mark apple as eaten
					MarkAppleAsEaten(*collidingApples[i]);
					RemoveAppleFromGrid(game.applesGrid, *collidingApples[i]);
				}

				// Increase eaten apples counter
				game.numEatenApples++;
				// Increase player speed
				if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::WithAcceleration)
				{
					game.player.speed += ACCELERATION;
				}
			}
		}

		bool isGameFinished = (game.numEatenApples == game.apples.size())
			&& !((std::uint8_t)game.options & (std::uint8_t)GameOptions::InfiniteApples);
		// Check collision with screen border
		if (isGameFinished || HasPlayerCollisionWithScreenBorder(game.player))
		{
			game.gameStateStack.push_back(GameState::GameOver);
			game.timeSinceGameOver = 0.f;

			// Find player in records table and update his score
			for (RecordsTableItem& item : game.recordsTable)
			{
				if (item.name == "You")
				{
					item.score = game.numEatenApples;
					break;
				}
			}

			// Sort records table
			std::sort(std::begin(game.recordsTable), std::end(game.recordsTable));
		}
	}

	void ShutdownPlayingState(Game& game)
	{

	}

	void InitGameOverState(Game& game)
	{
		game.timeSinceGameOver = 0.f;
	}

	void UpdateGameOverState(Game& game, float timeDelta)
	{
		game.timeSinceGameOver += timeDelta;
	}

	void ShutdownGameOverState(Game& game)
	{

	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		// Draw player
		DrawPlayer(game.player, window);
		// Draw apples
		for (Apple& apple: game.apples)
		{
			DrawApple(apple, window);
		}

		DrawUI(game.uiState, window);
	}

	void ShutdownGame(Game& game)
	{
		while (game.gameStateStack.size() > 0)
		{
			PopGameState(game);
		}
	}



}
