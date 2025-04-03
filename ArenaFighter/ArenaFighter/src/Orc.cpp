#include "Orc.h"
#include <iostream>
Orc::Orc(thor::ResourceHolder<sf::Texture, std::string>& t_holder)
	: m_holder(t_holder), m_orcHealthSystem(1000)
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

}

void Orc::render(sf::RenderWindow& window,bool debugMode)
{
	window.draw(m_orc);
	if (debugMode)
	{
		window.draw(m_hitbox);
	}
}

void Orc::initSprites()
{
	std::cout << "player created";
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
}

void Orc::animate(double dt)
{
	m_frameTimer = m_frameTimer + dt;

	if (m_frameTimer > m_timePerFrame)
	{
		if (m_orcState == 1) //sets appropraite frame for character state
		{
			m_orc.setTexture(m_holder["OrcSpriteWalk"]);
			m_orc.setTextureRect(sf::IntRect((m_col * 100), (m_walkRow * 100), m_frameSize, m_frameSize));
		}
		if (m_orcState == 0)
		{
			m_orc.setTexture(m_holder["OrcSpriteIdle"]);
			m_orc.setTextureRect(sf::IntRect((m_col * 100), (m_idleRow * 100), m_frameSize, m_frameSize));

		}
		m_col++;
		if ((m_col >= m_walkFrames && m_orcState == 1) || (m_col >= m_idleFrames && m_orcState == 0))//resets column if exceeded frames of that row
		{
			m_col = 0;
		}
		m_frameTimer = 0;
	}
}