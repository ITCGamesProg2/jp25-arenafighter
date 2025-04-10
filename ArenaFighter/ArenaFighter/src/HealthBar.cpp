#include "HealthBar.h"

HealthBar::HealthBar(sf::Vector2f t_position, float t_width, float t_height, int t_maxHealth) : m_maxHealth(t_maxHealth)
{
	m_healthBarBack.setSize({ t_width, t_height });
	m_healthBarBack.setFillColor(sf::Color::Red);
	m_healthBarBack.setPosition(t_position);

	m_healthBar.setSize({ t_width, t_height });
	m_healthBar.setFillColor(sf::Color::Green);
	m_healthBar.setPosition(t_position);
}

void HealthBar::onHealthChange(int newHealth)
{
	float percentage = static_cast<float>(newHealth) / m_maxHealth;
	sf::Vector2f size = m_healthBarBack.getSize();
	m_healthBar.setSize({ size.x * percentage, size.y });
}

void HealthBar::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_healthBarBack);
	t_window.draw(m_healthBar);
}

void HealthBar::setPosition(sf::Vector2f& t_playerPosition)
{
	m_healthBarBack.setPosition(t_playerPosition);
	m_healthBar.setPosition(t_playerPosition);
}
