#include "Orc.h"
#include <iostream>
Orc::Orc(thor::ResourceHolder<sf::Texture, std::string>& t_holder)
	: m_holder(t_holder), m_orcHealthSystem(100)
{
	initSprites();
}

sf::FloatRect Orc::getBounds() const
{
	return m_hitbox.getGlobalBounds();
}

sf::Vector2f Orc::getPosition() const
{
	return m_orc.getPosition();
}


void Orc::update(double dt)
{
	m_hitbox.setPosition(m_orc.getPosition().x, m_orc.getPosition().y - 5);
	animate(dt);
	updtateHealthbar();

}

void Orc::render(sf::RenderWindow& window,bool debugMode)
{
	window.draw(m_orc);
	if (debugMode)
	{
		window.draw(m_hitbox);
	}
	if (m_orcHealthSystem.getHealth() < 100)
	{
		window.draw(m_healthBarBack);
		window.draw(m_healthBar);
	}
}

void Orc::updtateHealthbar()
{
	float healthPercentage = static_cast<float>(m_orcHealthSystem.getHealth()) / m_orcHealthSystem.getMaxHealth();

	m_healthBar.setSize(sf::Vector2f{ 50 * healthPercentage, 15 });
	m_healthBar.setPosition(sf::Vector2f(m_orc.getPosition().x, m_orc.getPosition().y - 40));
	m_healthBarBack.setPosition(sf::Vector2f(m_orc.getPosition().x, m_orc.getPosition().y - 40));
}

void Orc::initSprites()
{
	std::cout << "Orc created";
	m_holder.acquire("OrcSpriteIdle", thor::Resources::fromFile<sf::Texture>("ASSETS/IMAGES/Orc/Orc/Orc-Idle.png"));
	m_holder.acquire("OrcSpriteWalk", thor::Resources::fromFile<sf::Texture>("ASSETS/IMAGES/Orc/Orc/Orc-Walk.png"));
	m_orc.setTexture(m_holder["OrcSpriteIdle"]);

	m_orc.setTextureRect(sf::IntRect(0, 0, m_frameSize, m_frameSize));

	m_orc.setOrigin(m_frameSize / 2, m_frameSize / 2);
	m_orc.setScale(3, 3);
	m_orc.setPosition(300, 300);

	m_hitbox.setSize(sf::Vector2f(40, 50));
	m_hitbox.setFillColor(sf::Color::Transparent);
	m_hitbox.setOrigin(m_hitbox.getGlobalBounds().width / 2, m_hitbox.getGlobalBounds().height / 2);
	m_hitbox.setOutlineColor(sf::Color::Green);
	m_hitbox.setOutlineThickness(1);

	m_healthBar.setSize({ 50, 15 });
	m_healthBar.setOrigin(m_healthBar.getSize().x / 2, m_healthBar.getSize().y / 2);
	m_healthBar.setFillColor(sf::Color::Green);
	m_healthBar.setPosition(m_orc.getPosition().x, m_orc.getPosition().y - 40);

	m_healthBarBack.setFillColor(sf::Color::Red);
	m_healthBarBack.setSize({ 50, 15 });
	m_healthBarBack.setOrigin(m_healthBarBack.getSize().x / 2, m_healthBarBack.getSize().y / 2);
	m_healthBarBack.setPosition(m_orc.getPosition().x, m_orc.getPosition().y - 40);
}

void Orc::animate(double dt)
{
	m_frameTimer = m_frameTimer + dt;

	if (m_frameTimer > m_timePerFrame)
	{
		if (m_orcState == OrcState::WALKING) //sets appropraite frame for character state
		{
			m_orc.setTexture(m_holder["OrcSpriteWalk"]);
			m_orc.setTextureRect(sf::IntRect((m_col * 100), (m_walkRow * 100), m_frameSize, m_frameSize));
		}
		if (m_orcState == OrcState::IDLE)
		{
			m_orc.setTexture(m_holder["OrcSpriteIdle"]);
			m_orc.setTextureRect(sf::IntRect((m_col * 100), (m_idleRow * 100), m_frameSize, m_frameSize));

		}
		m_col++;
		if ((m_col >= m_walkFrames && m_orcState == OrcState::WALKING) || (m_col >= m_idleFrames && m_orcState == OrcState::IDLE))//resets column if exceeded frames of that row
		{
			m_col = 0;
		}
		m_frameTimer = 0;
	}
}