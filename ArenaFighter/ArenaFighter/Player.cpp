#include "Player.h"
#include <iostream>
Player::Player(thor::ResourceHolder<sf::Texture, std::string>& t_holder)
	: m_holder(t_holder)
{
	initSprites();
}

void Player::handleKeyInput()
{
	m_playerState = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_player.move(0, -m_speed);
		m_playerState = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_player.move(0,m_speed);
		m_playerState = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_player.move( -m_speed,0);
		m_playerState = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_player.move(m_speed, 0);
		m_playerState = 1;
	}

}


void Player::update(double dt)
{
	handleKeyInput();
	animate(dt);
}

void Player::render(sf::RenderWindow& window)
{
	window.draw(m_player);
}

void Player::initSprites()
{
	std::cout << "player created";
	m_holder.acquire("playerSprite", thor::Resources::fromFile<sf::Texture>("ASSETS/IMAGES/Soldier/Soldier/Soldier.png"));

	m_player.setTexture(m_holder["playerSprite"]);


	m_player.setTextureRect(sf::IntRect(0, 0, m_frameSize, m_frameSize));
	m_player.setScale(3, 3);

}

void Player::animate(double dt)
{
	m_frameTimer = m_frameTimer + dt;

	if (m_frameTimer > m_timePerFrame)
	{
		if (m_playerState == 1) //sets appropraite frame for character state
			m_player.setTextureRect(sf::IntRect((m_col*100),(m_walkRow*100) , m_frameSize,m_frameSize));
		if (m_playerState == 0)
			m_player.setTextureRect(sf::IntRect((m_col * 100), (m_idleRow * 100), m_frameSize, m_frameSize));
		m_col++;

		if ((m_col >= m_walkFrames && m_playerState==1) || (m_col >= m_idleFrames && m_playerState == 0))//resets column if exceeded frames of that row
		{
			m_col = 0;
		}
		m_frameTimer = 0;
	}
}