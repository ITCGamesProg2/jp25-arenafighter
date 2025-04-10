#pragma once
#include <SFML/Graphics.hpp>

class PickupStrategy
{
public:
	virtual ~PickupStrategy() = default;

	virtual void applyPotionEffect() = 0;
	virtual sf::IntRect getTextureRect() const = 0;
};