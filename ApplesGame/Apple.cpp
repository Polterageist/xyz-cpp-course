#include "Apple.h"
#include "GameSettings.h"

#include <cstdlib>

namespace ApplesGame
{
	void InitApple(Apple& apple, const sf::Texture& texture)
	{
		// init apple state
		apple.position.x = (float)(rand() % SCREEN_WIDTH);
		apple.position.y = (float)(rand() % SCREEN_HEGHT);

		// Init sprite
		apple.sprite.setTexture(texture);
		apple.sprite.setOrigin(GetSpriteOrigin(apple.sprite, { 0.5f, 0.5f })); // We need to use texture as origin ignores scale
		apple.sprite.setScale(GetSpriteScale(apple.sprite, { APPLE_SIZE, APPLE_SIZE }));
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		apple.sprite.setPosition(OurVectorToSf(apple.position));
		window.draw(apple.sprite);
	}

}