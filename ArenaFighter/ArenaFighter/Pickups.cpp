#include "Pickups.h"

Pickup::Pickup(thor::ResourceHolder<sf::Texture, std::string>& t_holder) : m_holder(t_holder)
{
	initPickups();
}

void Pickup::initPickups()
{
	m_holder.acquire("tileMapPickup", thor::Resources::fromFile<sf::Texture>("ASSETS/IMAGES/Dungeon_Tileset.png"));
	m_pickupSprite.setTexture(m_holder["tileMapPickup"]);


	m_hitbox.setSize(sf::Vector2f{ 32, 32 });
	m_hitbox.setOrigin(m_hitbox.getGlobalBounds().width / 2, m_hitbox.getGlobalBounds().height / 2);
	m_hitbox.setFillColor(sf::Color::Transparent);
	m_hitbox.setOutlineColor(sf::Color::Green);
	m_hitbox.setOutlineThickness(1);

	//// Roll a random number from 1-2 and set type based on this number
	//int randomNumber = rand() % 2;
	//if (randomNumber == 0)
	//{
	//	m_pickupType = PickupType::POTION;
	//}
	//if (randomNumber == 1)
	//{
	//	m_pickupType = PickupType::POSION;
	//}
	m_pickupType = PickupType::POTION;


	// Based on pickup type, change texture
	if (m_pickupType == PickupType::POTION)
	{
		//144x 144y
		m_pickupSprite.setTextureRect(sf::IntRect{ 144, 128, 16, 16 });
		m_pickupSprite.setOrigin(m_pickupSprite.getGlobalBounds().width / 2, m_pickupSprite.getGlobalBounds().height / 2);
		m_pickupSprite.setScale(3.0, 3.0);
		m_pickupSprite.setPosition(sf::Vector2f{ 600,200 });
	}

	m_hitbox.setPosition(m_pickupSprite.getPosition());
}

void Pickup::renderickups(sf::RenderWindow& t_window, bool t_debugMode)
{
	t_window.draw(m_pickupSprite);
	if (t_debugMode)
	{
		t_window.draw(m_hitbox);
	}

}

sf::FloatRect Pickup::getHitbox() const
{
	return m_hitbox.getGlobalBounds();
}

sf::Vector2f Pickup::returnHitboxPosition() const
{
	return m_hitbox.getPosition();
}


