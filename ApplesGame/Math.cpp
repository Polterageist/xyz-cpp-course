#include "Math.h"

namespace ApplesGame
{
	sf::Vector2f OurVectorToSf(const Vector2D& v)
	{
		return sf::Vector2f(v.x, v.y);
	}
}
