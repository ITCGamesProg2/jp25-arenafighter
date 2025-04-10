#pragma once
#include "HealthObserverInterface.h"
#include <SFML/Graphics.hpp>

class HealthBar : public HealthObserverInterface
{
public:
	HealthBar(sf::Vector2f t_position, float t_width, float t_height, int t_maxHealth);
	void onHealthChange(int newHealth) override;
	void render(sf::RenderWindow& t_window);

	void setPosition(sf::Vector2f& t_playerPosition);


private:
	sf::RectangleShape m_healthBar;
	sf::RectangleShape m_healthBarBack;
	int m_maxHealth;
};