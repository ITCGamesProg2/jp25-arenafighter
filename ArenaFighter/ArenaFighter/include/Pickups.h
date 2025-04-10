#pragma once

#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include "PickupStrategy.h"
#include "HealthPotion.h"
#include "PosionPotion.h"
#include <memory>

enum class PickupType
{
	POTION,
	POISON
};

class Pickup
{
public:
	Pickup(thor::ResourceHolder <sf::Texture, std::string>& t_holder);

	void initPickups();

	void renderickups(sf::RenderWindow& t_window, bool t_debugMode);

	sf::FloatRect getHitbox() const;
	sf::Vector2f returnHitboxPosition() const;

	

	PickupType getType();

	void applyPickupEffect();
private:

	sf::Sprite m_pickupSprite;
	PickupType m_pickupType;
	sf::RectangleShape m_hitbox;

	thor::ResourceHolder<sf::Texture, std::string>& m_holder;
	std::unique_ptr<PickupStrategy> m_potionStrat;
};
