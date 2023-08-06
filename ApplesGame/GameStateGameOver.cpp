#include "GameStateGameOver.h"
#include <assert.h>
#include "Game.h"

namespace ApplesGame
{
	void InitGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.timeSinceGameOver = 0.f;

		data.gameOverText.setFont(data.font);
		data.gameOverText.setCharacterSize(48);
		data.gameOverText.setStyle(sf::Text::Bold);
		data.gameOverText.setFillColor(sf::Color::Red);
		data.gameOverText.setString("GAME OVER");
		data.gameOverText.setOrigin(GetTextOrigin(data.gameOverText, { 0.5f, 0.5f }));
		
		data.optionsText.setFont(data.font);
		data.optionsText.setCharacterSize(24);
		data.optionsText.setFillColor(sf::Color::White);
		data.optionsText.setString("Press 1 to toggle infinite apples, 2 to toggle acceleration, Space to restart");
		data.optionsText.setOrigin(GetTextOrigin(data.optionsText, { 0.5f, 1.f }));
		
		data.recordsTableText.setFont(data.font);
		data.recordsTableText.setCharacterSize(24);
		data.recordsTableText.setFillColor(sf::Color::Green);
		data.recordsTableText.setString("Records:\nPlayer: 999\nPlayer: 999\nPlayer: 999\nPlayer: 999\nPlayer: 999");
		data.recordsTableText.setOrigin(GetTextOrigin(data.recordsTableText, { 0.5f, 0.f }));
	}

	void ShutdownGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				SwitchGameState(game, GameStateType::Playing);
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				// Exit the game
				PushGameState(game, GameStateType::ExitDialog, true);
			}
			else if (event.key.code == sf::Keyboard::Num1)
			{
				game.options = (GameOptions)((std::uint8_t)game.options ^ (std::uint8_t)GameOptions::InfiniteApples);
			}
			else if (event.key.code == sf::Keyboard::Num2)
			{
				game.options = (GameOptions)((std::uint8_t)game.options ^ (std::uint8_t)GameOptions::WithAcceleration);
			}
		}
	}

	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game, float timeDelta)
	{
		data.timeSinceGameOver += timeDelta;

		sf::Color gameOverTextColor = (int)data.timeSinceGameOver % 2 ? sf::Color::Red : sf::Color::Yellow;
		data.gameOverText.setFillColor(gameOverTextColor);

		data.recordsTableText.setString("Records:");
		for (const RecordsTableItem& item : game.recordsTable)
		{
			data.recordsTableText.setString(data.recordsTableText.getString() + "\n" + item.name + ": " + std::to_string(item.score));
		}
		data.recordsTableText.setOrigin(GetTextOrigin(data.recordsTableText, { 0.5f, 0.f }));

		bool isInfiniteApples = ((std::uint8_t)game.options & (std::uint8_t)GameOptions::InfiniteApples) != (std::uint8_t)GameOptions::Empty;
		bool isWithAcceleration = ((std::uint8_t)game.options & (std::uint8_t)GameOptions::WithAcceleration) != (std::uint8_t)GameOptions::Empty;
		std::string optionsText = "Press 1 to toggle infinite apples: " + std::string(isInfiniteApples ? "ON" : "OFF") + "\n"
			+ "Press 2 to toggle acceleration: " + std::string(isWithAcceleration ? "ON" : "OFF") + "\n"
			+ "Press Space to restart game";
		data.optionsText.setString(optionsText);
		data.optionsText.setOrigin(GetTextOrigin(data.optionsText, { 0.5f, 1.f }));
	}

	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		data.gameOverText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f);
		window.draw(data.gameOverText);

		data.recordsTableText.setPosition(viewSize.x / 2.f, 30.f);
		window.draw(data.recordsTableText);

		data.optionsText.setPosition(viewSize.x / 2.f, viewSize.y - 10.f);
		window.draw(data.optionsText);
	}
}
