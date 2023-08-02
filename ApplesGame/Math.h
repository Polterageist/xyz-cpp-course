#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	struct Vector2D
	{
		float x = 0.f;
		float y = 0.f;
	};

	Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs);


	typedef Vector2D Position;

	sf::Vector2f OurVectorToSf(const Vector2D& v);
	sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, const Vector2D& desiredSize);
	sf::Vector2f GetSpriteOrigin(const sf::Sprite& sprite, const Vector2D& relativePosition);
	sf::Vector2f GetTextOrigin(const sf::Text& text, const Vector2D& relativePosition);


	bool IsPointInRect(Vector2D point, Vector2D rectTL, Vector2D rectBR);
}
