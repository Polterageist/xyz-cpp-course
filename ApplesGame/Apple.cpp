#include "Apple.h"
#include "GameSettings.h"

#include <cstdlib>

namespace ApplesGame
{
	void InitApple(Apple& apple)
	{
		// init apple state
		apple.position.x = (float)(rand() % SCREEN_WIDTH);
		apple.position.y = (float)(rand() % SCREEN_HEGHT);

		// Init apple representation
		apple.shape.setRadius(APPLE_SIZE / 2.f);
		apple.shape.setFillColor(sf::Color::Red);
		apple.shape.setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
		apple.shape.setPosition(OurVectorToSf(apple.position));
	}
}
