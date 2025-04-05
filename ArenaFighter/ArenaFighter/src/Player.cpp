#include "Player.h"
#include <iostream>
Player::Player(thor::ResourceHolder<sf::Texture, std::string>& t_holder)
	: m_holder(t_holder), m_playerState(PlayerState::IDLE), m_playerDirection(Direction::RIGHT)
{
	initSprites();
}

void Player::handleKeyInput()
{
	m_playerState = PlayerState::IDLE;
	m_hitbox.setSize(sf::Vector2f(40, 50));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_player.move(0, -m_speed);
		m_playerState = PlayerState::WALKING;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_player.move(0,m_speed);
		m_playerState = PlayerState::WALKING;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_player.move( -m_speed,0);
		m_playerState = PlayerState::WALKING;
		m_player.setScale(-3.0, 3.0);
		m_playerDirection = Direction::LEFT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_player.move(m_speed, 0);
		m_playerState = PlayerState::WALKING;
		m_player.setScale(3.0, 3.0);
		m_playerDirection = Direction::RIGHT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_playerState = PlayerState::ATTACKING;
		if (m_playerDirection == Direction::RIGHT)
		{
			m_hitbox.setSize(sf::Vector2f(80, 50));
			m_hitbox.setPosition(m_player.getPosition().x, m_player.getPosition().y - 5);
		}
		else
		{
			m_hitbox.setSize(sf::Vector2f(80, 50));
			m_hitbox.setPosition(m_player.getPosition().x - 40, m_player.getPosition().y - 5);
		}
	}
	if (m_playerState == PlayerState::IDLE && m_col >= m_idleFrames)
	{
		m_col = 0;
	}
}

sf::FloatRect Player::getBounds() const
{
	return m_hitbox.getGlobalBounds();
}

sf::Vector2f Player::getOrigin()
{
	return m_player.getOrigin();
}

sf::Vector2f Player::getPosition() const
{
	return m_player.getPosition();
}



void Player::update(double dt)
{
	m_hitbox.setPosition(m_player.getPosition().x, m_player.getPosition().y - 5);
	handleKeyInput();
	animate(dt);
}

void Player::render(sf::RenderWindow& window, bool t_debugMode)
{
	window.draw(m_player);
	if (t_debugMode)
	{
		window.draw(m_hitbox);
	}
}

void Player::initSprites()
{
	std::cout << "player created";
	m_holder.acquire("playerSpriteIdle", thor::Resources::fromFile<sf::Texture>("ASSETS/IMAGES/Soldier/Soldier/Soldier-Idle.png"));
	m_holder.acquire("playerSpriteWalk", thor::Resources::fromFile<sf::Texture>("ASSETS/IMAGES/Soldier/Soldier/Soldier-Walk.png"));
	m_holder.acquire("playerAttackOne", thor::Resources::fromFile<sf::Texture>("ASSETS/IMAGES/Soldier/Soldier/Soldier-Attack01.png"));
	m_player.setTexture(m_holder["playerSpriteIdle"]);


	m_player.setTextureRect(sf::IntRect(0, 0, m_frameSize, m_frameSize));

	m_player.setOrigin(m_frameSize / 2, m_frameSize / 2);
	m_player.setScale(3, 3);

	m_hitbox.setSize(sf::Vector2f(40, 50));
	m_hitbox.setFillColor(sf::Color::Transparent);
	m_hitbox.setOrigin(m_hitbox.getGlobalBounds().width / 2, m_hitbox.getGlobalBounds().height / 2);
	m_hitbox.setOutlineColor(sf::Color::Green);
	m_hitbox.setOutlineThickness(1);
}

void Player::animate(double dt)
{
	m_frameTimer = m_frameTimer + dt;

	if (m_frameTimer > m_timePerFrame)
	{
		if (m_playerState == PlayerState::WALKING) //sets appropraite frame for character state
		{
			m_player.setTexture(m_holder["playerSpriteWalk"]);
			m_player.setTextureRect(sf::IntRect((m_col * 100), (m_walkRow * 100), m_frameSize, m_frameSize));
		}
		if (m_playerState == PlayerState::IDLE)
		{
			m_player.setTexture(m_holder["playerSpriteIdle"]);
			m_player.setTextureRect(sf::IntRect((m_col * 100), (m_idleRow * 100), m_frameSize, m_frameSize));	
		}
		if (m_playerState == PlayerState::ATTACKING)
		{
			m_player.setTexture(m_holder["playerAttackOne"]);
			m_player.setTextureRect(sf::IntRect((m_col * 100), (m_idleRow * 100), m_frameSize, m_frameSize));
		}
		m_col++;
		//if ((m_col >= m_idleFrames && m_playerState == PlayerState::IDLE) || (m_col >= m_walkFrames && m_playerState == PlayerState::WALKING ))//resets column if exceeded frames of that row
		if (m_col >= m_idleFrames || m_col >= m_walkFrames)
		{
			m_col = 0;
		}
		m_frameTimer = 0;
	}
}

bool Player::isAttacking()
{
	if (m_playerState == PlayerState::ATTACKING)
	{
		return true;
	}
	return false;
}

bool Player::updateGrid(int grid) //returns true if player has moved to a new grid
{
	if (grid != m_currentGrid)
	{
		m_currentGrid = grid;
		return true;
	}
	return false;
}