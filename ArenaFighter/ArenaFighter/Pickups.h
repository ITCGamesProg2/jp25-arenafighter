#pragma once

#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>


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
private:

	sf::Sprite m_pickupSprite;
	PickupType m_pickupType;
	sf::RectangleShape m_hitbox;

	thor::ResourceHolder<sf::Texture, std::string>& m_holder;
};
