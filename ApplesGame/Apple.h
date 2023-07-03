#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	struct Apple
	{
		Position position;
		sf::CircleShape shape;
	};

	void InitApple(Apple& apple);
}
