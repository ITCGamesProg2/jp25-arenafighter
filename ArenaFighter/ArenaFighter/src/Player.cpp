#include "Player.h"
#include <iostream>
Player::Player(thor::ResourceHolder<sf::Texture, std::string>& t_holder)
	: m_holder(t_holder), m_playerState(PlayerState::IDLE), m_playerDirection(Direction::RIGHT), m_playerHealthSystem(200)
{
	initSprites();

	// Load in the shader
	if (!m_playerOutline.loadFromFile("ASSETS/SHADERS/playerOutline.frag", sf::Shader::Fragment))
	{
		std::cout << "Error loading player outline shader file!\n";
	}
	else
	{
		m_shaderLoaded = true;
		m_playerOutline.setUniform("texture", sf::Shader::CurrentTexture);
		m_playerOutline.setUniform("outlineColour", sf::Glsl::Vec4(0.5f, 0.0f, 0.5f, 1.0f));
		m_playerOutline.setUniform("outlineThickness", 0.5f);
	}
	sf::Vector2f healthBarInitPos = m_player.getPosition();
	m_healthBarFinal = std::make_unique<HealthBar>(healthBarInitPos, 50.0f, 15.0f, m_playerHealthSystem.getMaxHealth());
	m_playerHealthSystem.attachObserver(m_healthBarFinal.get());
}

void Player::handleKeyInput()
{
	m_playerState = PlayerState::IDLE;
	m_hitbox.setSize(sf::Vector2f(40, 50));
	sf::Vector2f movement(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		movement.y = -1;
		m_playerState = PlayerState::WALKING;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movement.y = 1;
		m_playerState = PlayerState::WALKING;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movement.x = -1;
		m_playerState = PlayerState::WALKING;
		m_player.setScale(-3.0, 3.0);
		m_playerDirection = Direction::LEFT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movement.x = 1;
		m_playerState = PlayerState::WALKING;
		m_player.setScale(3.0, 3.0);
		m_playerDirection = Direction::RIGHT;
	}

	if (movement.x != 0 || movement.y != 0)
	{
		movement = thor::unitVector(movement);
		movement.x = movement.x * m_speed;
		movement.y = movement.y * m_speed;
		m_player.move(movement);
	}

	if (m_player.getPosition().x > 1355) //border checking for player (custom values to match map wall sizes)
	{
		m_player.setPosition(1355, m_player.getPosition().y);
	}

	if (m_player.getPosition().x < 50)
	{
		m_player.setPosition(50, m_player.getPosition().y);
	}

	if (m_player.getPosition().y > 745)
	{
		m_player.setPosition(m_player.getPosition().x, 745);
	}

	if (m_player.getPosition().y < 30)
	{
		m_player.setPosition(m_player.getPosition().x, 30);
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
	if (m_playerHealthSystem.getHealth() <= 0)
	{
		m_playerState = PlayerState::DEAD;
	}
	if (m_playerState != PlayerState::DEAD)
	{
		handleKeyInput();
	}
	animate(dt);
	updateHealthBar();
}

void Player::render(sf::RenderWindow& window, bool t_debugMode)
{
	sf::RenderStates states;
	if (m_shaderLoaded)
	{
		states.shader = &m_playerOutline;
	}

	window.draw(m_player, states);
	if (t_debugMode)
	{
		window.draw(m_hitbox);
	}
	if (m_playerHealthSystem.getHealth() < m_playerHealthSystem.getMaxHealth())
	{
		m_healthBarFinal->render(window);
	}
}

void Player::initSprites()
{
	std::cout << "player created";
	m_holder.acquire("playerSpriteIdle", thor::Resources::fromFile<sf::Texture>("ASSETS/IMAGES/Soldier/Soldier/Soldier-Idle.png"));
	m_holder.acquire("playerSpriteWalk", thor::Resources::fromFile<sf::Texture>("ASSETS/IMAGES/Soldier/Soldier/Soldier-Walk.png"));
	m_holder.acquire("playerAttackOne", thor::Resources::fromFile<sf::Texture>("ASSETS/IMAGES/Soldier/Soldier/Soldier-Attack01.png"));
	m_holder.acquire("playerDeath", thor::Resources::fromFile<sf::Texture>("ASSETS/IMAGES/Soldier/Soldier/Soldier-Death.png"));
	m_player.setTexture(m_holder["playerSpriteIdle"]);


	m_player.setTextureRect(sf::IntRect(0, 0, m_frameSize, m_frameSize));

	m_player.setOrigin(m_frameSize / 2, m_frameSize / 2);
	m_player.setScale(3, 3);

	m_player.setPosition(500, 500);

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
		if (m_playerState == PlayerState::DEAD)
		{
			m_player.setTexture(m_holder["playerDeath"]);
			m_player.setTextureRect(sf::IntRect((m_col * 100), (m_idleRow * 100), m_frameSize, m_frameSize));
			if (m_col > 3)
				m_gameOver=true;
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

void Player::updateHealthBar()
{
	sf::Vector2f newPosition = m_player.getPosition();
	newPosition.x -= 28;
	newPosition.y -= 60;
	m_healthBarFinal->setPosition(newPosition);
}

void Player::keepPlayerInBounds()
{
	sf::Vector2f playerPosition = m_player.getPosition();

	if (m_player.getPosition().x >= 1360)
	{
		playerPosition.x -= 5;
		m_player.setPosition(playerPosition);
	}
	if (m_player.getPosition().x <= 50)
	{
		playerPosition.x += 5;
		m_player.setPosition(playerPosition);
	}
	if (m_player.getPosition().y >= 750)
	{
		playerPosition.y -= 5;
		m_player.setPosition(playerPosition);
	}
	if (m_player.getPosition().y <= 50)
	{
		playerPosition.y += 5;
		m_player.setPosition(playerPosition);
	}
}

void Player::setPosition(sf::Vector2f t_position)
{
	m_player.setPosition(t_position);
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



void Player::respawn()
{
	m_gameOver = false;
	m_playerState = PlayerState::IDLE;
	m_player.setPosition(100, 100);
	m_playerHealthSystem.setHealth(m_playerHealthSystem.getMaxHealth());
}

bool Player::isGameOver()
{
	return m_gameOver;
}