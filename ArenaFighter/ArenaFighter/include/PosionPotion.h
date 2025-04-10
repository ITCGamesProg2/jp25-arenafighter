#pragma once
#include "PickupStrategy.h"
#include <iostream>

class PoisonPotion : public PickupStrategy
{
public:
	void applyPotionEffect() override
	{
		std::cout << "Poison damaged player!\n";
	}

	sf::IntRect getTextureRect() const override
	{
		return sf::IntRect{ 112, 128,16,16 };
	}
};