#include "Pickups.h"

Pickup::Pickup(thor::ResourceHolder<sf::Texture, std::string>& t_holder) : m_holder(t_holder)
{
	// Set seed for random number gen
	srand(time(NULL));
	m_holder.acquire("tileMapPickup", thor::Resources::fromFile<sf::Texture>("ASSETS/IMAGES/Dungeon_Tileset.png"));
	initPickups();
	
}

void Pickup::initPickups()
{
	m_pickupSprite.setTexture(m_holder["tileMapPickup"]);
	m_pickupSprite.setOrigin({ 16,16 });
	m_pickupSprite.setScale(2.0f, 2.0f);

	m_hitbox.setSize(sf::Vector2f{ 32, 32 });
	m_hitbox.setOrigin({16,16});
	m_hitbox.setFillColor(sf::Color::Transparent);
	m_hitbox.setOutlineColor(sf::Color::Green);
	m_hitbox.setOutlineThickness(1);


	

	// Roll a random number from 0-1 and set type based on this number
	int randomNumber = rand() % 2;
	if (randomNumber == 0)
	{
		m_potionStrat = std::make_unique<HealthPotion>();
		m_pickupType = PickupType::POTION;
	}
	else
	{
		m_potionStrat = std::make_unique<PoisonPotion>();
		m_pickupType = PickupType::POISON;
	}

	m_pickupSprite.setTextureRect(m_potionStrat->getTextureRect());
	
	sf::Vector2f newPosition = { static_cast<float>(rand() % 1200) + 100, static_cast<float>(rand() % 600) + 100 };
	m_pickupSprite.setPosition(newPosition);
	m_hitbox.setPosition(m_pickupSprite.getPosition().x - 15, m_pickupSprite.getPosition().y - 15);
	
	
	
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



PickupType Pickup::getType()
{
	return m_pickupType;
}

void Pickup::applyPickupEffect()
{
	if (m_potionStrat)
	{
		m_potionStrat->applyPotionEffect();
	}
}


