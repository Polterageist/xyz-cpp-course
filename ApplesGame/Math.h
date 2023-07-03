#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	struct Vector2D
	{
		float x = 0.f;
		float y = 0.f;
	};

	typedef Vector2D Position;

	sf::Vector2f OurVectorToSf(const Vector2D& v);
}
