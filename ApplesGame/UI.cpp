#include "UI.h"
#include "Game.h"
#include <string>

namespace ApplesGame
{
	void InitUI(UIState& uiState, const sf::Font& font) 
	{
		uiState.scoreText.setFont(font);
		uiState.scoreText.setCharacterSize(24);
		uiState.scoreText.setFillColor(sf::Color::Yellow);

		uiState.inputHintText.setFont(font);
		uiState.inputHintText.setCharacterSize(24);
		uiState.inputHintText.setFillColor(sf::Color::White);
		uiState.inputHintText.setString("Use arrow keys to move, ESC to exit");
		uiState.inputHintText.setOrigin(GetTextOrigin(uiState.inputHintText, { 1.f, 0.f } ));

		uiState.isGameOverTextVisible = false;
		uiState.gameOverText.setFont(font);
		uiState.gameOverText.setCharacterSize(48);
		uiState.gameOverText.setStyle(sf::Text::Bold);
		uiState.gameOverText.setFillColor(sf::Color::Red);
		uiState.gameOverText.setString("GAME OVER");
		uiState.gameOverText.setOrigin(GetTextOrigin(uiState.gameOverText, { 0.5f, 0.5f }));

		uiState.optionsText.setFont(font);
		uiState.optionsText.setCharacterSize(24);
		uiState.optionsText.setFillColor(sf::Color::White); 
		uiState.optionsText.setString("Press 1 to toggle infinite apples, 2 to toggle acceleration, Space to restart");
		uiState.optionsText.setOrigin(GetTextOrigin(uiState.optionsText, { 0.5f, 1.f }));

		uiState.recordsTableText.setFont(font);
		uiState.recordsTableText.setCharacterSize(24);
		uiState.recordsTableText.setFillColor(sf::Color::Green);
		uiState.recordsTableText.setString("Records:\nPlayer: 999\nPlayer: 999\nPlayer: 999\nPlayer: 999\nPlayer: 999");
		uiState.recordsTableText.setOrigin(GetTextOrigin(uiState.recordsTableText, { 0.5f, 0.f }));
	}

	void UpdateUI(UIState& uiState, const struct GameState& gameState, float timeDelta)
	{
		uiState.scoreText.setString("Apples eaten: " + std::to_string(gameState.numEatenApples));

		uiState.isGameOverTextVisible = gameState.isGameOver;
		sf::Color gameOverTextColor = (int)gameState.timeSinceGameOver % 2? sf::Color::Red : sf::Color::Yellow;
		uiState.gameOverText.setFillColor(gameOverTextColor);
		
		uiState.recordsTableText.setString("Records:");
		for (const RecordsTableItem& item : gameState.recordsTable)
		{
			uiState.recordsTableText.setString(uiState.recordsTableText.getString() + "\n" + item.name + ": " + std::to_string(item.score));
		}
		uiState.recordsTableText.setOrigin(GetTextOrigin(uiState.recordsTableText, { 0.5f, 0.f }));

		bool isInfiniteApples = ((std::uint8_t)gameState.options & (std::uint8_t)GameOptions::InfiniteApples) != (std::uint8_t)GameOptions::Empty;
		bool isWithAcceleration = ((std::uint8_t)gameState.options & (std::uint8_t)GameOptions::WithAcceleration) != (std::uint8_t)GameOptions::Empty;
		std::string optionsText = "Press 1 to toggle infinite apples: " + std::string(isInfiniteApples ? "ON" : "OFF") + "\n"
			+ "Press 2 to toggle acceleration: " + std::string(isWithAcceleration ? "ON" : "OFF") + "\n"
			+ "Press Space to restart game";
		uiState.optionsText.setString(optionsText);
		uiState.optionsText.setOrigin(GetTextOrigin(uiState.optionsText, { 0.5f, 1.f }));
	}

	void DrawUI(UIState& uiState, sf::RenderWindow& window)
	{
		uiState.scoreText.setPosition(10.f, 10.f);
		window.draw(uiState.scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		uiState.inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(uiState.inputHintText);

		if (uiState.isGameOverTextVisible)
		{
			uiState.gameOverText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f);
			window.draw(uiState.gameOverText);

			uiState.recordsTableText.setPosition(viewSize.x / 2.f, 30.f);
			window.draw(uiState.recordsTableText);

			uiState.optionsText.setPosition(viewSize.x / 2.f, viewSize.y - 10.f);
			window.draw(uiState.optionsText);
		}
	}

}

