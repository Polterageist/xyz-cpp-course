#pragma once
#include <SFML/Graphics.hpp>
#include "Vector.h"

namespace ApplesGame
{
	sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, const Vector2Df& desiredSize);
	sf::Vector2f GetItemOrigin(const sf::Sprite& sprite, const Vector2Df& relativePosition);
	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);

	// Helper method for organizing text items
	enum class Orientation
	{
		Horizontal,
		Vertical
	};

	enum class Alignment
	{
		Min, // Left or Top
		Middle,
		Max // Right or Bottom
	};

	void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin);

	template<typename T>
	bool IsPointInRect(const Vector2D<T>& point, const Vector2D<T>& rectTL, const Vector2D<T>& rectBR)
	{
		if (point.x < rectTL.x || point.x > rectBR.x)
		{
			return false;
		}
		if (point.y < rectTL.y || point.y > rectBR.y)
		{
			return false;
		}
		return true;
	}
}

template<>
struct std::hash<ApplesGame::Vector2Di>
{
	std::size_t operator()(const ApplesGame::Vector2Di& v) const noexcept
	{
		return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
	}
};
