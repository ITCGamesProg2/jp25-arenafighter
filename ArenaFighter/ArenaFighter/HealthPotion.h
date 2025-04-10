#pragma once
#include "PickupStrategy.h"
#include <iostream>

class HealthPotion : public PickupStrategy
{
public:
	void applyPotionEffect() override
	{
		std::cout << "Potion Healed Player\n";
	}

	sf::IntRect getTextureRect() const override
	{
		return sf::IntRect{ 144,128,16,16 };
	}
};