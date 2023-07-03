#include "Player.h"
#include "GameSettings.h"
#include "Apple.h"

namespace ApplesGame
{
	void InitPlayer(Player& player)
	{
		// Init player state
		player.position.x = (float)SCREEN_WIDTH / 2.f;
		player.position.y = (float)SCREEN_HEGHT / 2.f;
		player.speed = INITIAL_SPEED;
		player.direction = PlayerDirection::Up;

		// Init player representation
		player.shape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
		player.shape.setFillColor(sf::Color::Green);
		player.shape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
		player.shape.setPosition(OurVectorToSf(player.position));
	}

	void UpdatePlayer(Player& player, float timeDelta)
	{
		// Move player
		if (player.direction == PlayerDirection::Up)
		{
			player.position.y -= player.speed * timeDelta;
		}
		else if (player.direction == PlayerDirection::Right)
		{
			player.position.x += player.speed * timeDelta;
		}
		else if (player.direction == PlayerDirection::Down)
		{
			player.position.y += player.speed * timeDelta;
		}
		else if (player.direction == PlayerDirection::Left)
		{
			player.position.x -= player.speed * timeDelta;
		}

		player.shape.setPosition(OurVectorToSf(player.position));
	}

	bool HasPlayerCollisionWithScreenBorder(const Player& player)
	{
		return (player.position.x - PLAYER_SIZE / 2.f < 0) ||
			(player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH) ||
			(player.position.y - PLAYER_SIZE / 2.f < 0) ||
			(player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEGHT);
	}

	bool HasPlayerCollisionWithApple(const Player& player, const Apple& apple)
	{
		float dx = player.position.x - apple.position.x;
		float dy = player.position.y - apple.position.y;
		float distance = sqrt(dx * dx + dy * dy);
		return distance < (PLAYER_SIZE + APPLE_SIZE) / 2.f;
	}
}
