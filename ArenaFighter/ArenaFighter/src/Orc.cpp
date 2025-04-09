#include "Orc.h"
#include <iostream>
#include <Thor/Vectors/VectorAlgebra2D.hpp>

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

void Orc::setMovePath(std::vector<int> cellPath)
{
	movePath = cellPath;//sets to new path
	nextCell = movePath.back();//sets the next cell for orc to go to
	movePath.pop_back();//removes orc current cell location
	if (m_orcState != OrcState::DIE)
	{
		if (!movePath.empty())
		{
			nextCell = movePath.back();//sets the next cell for orc to go to
			m_orcState = OrcState::WALKING; //orc needs to walk to destination
		}
		else
		{
			m_orcState = OrcState::ATTACKING; //orc is in same area as destination
		}
	}
}

void Orc::update(double dt)
{
	m_hitbox.setPosition(m_orc.getPosition().x, m_orc.getPosition().y - 5);
	animate(dt);
	updtateHealthbar();

	gridToCoordinate();
	m_moveNormal = nextCoordinates - m_orc.getPosition();
	m_moveNormal = thor::unitVector (m_moveNormal);//gets move normal
	m_moveNormal = m_moveNormal * m_speed;

	if (m_orcState == OrcState::ATTACKING)
	{
		m_damageTimer += dt;
	}

	float distanceX = m_orc.getPosition().x - nextCoordinates.x;
	float distanceY = m_orc.getPosition().y - nextCoordinates.y;
	float distance = std::sqrt((distanceX * distanceX) + (distanceY * distanceY)); //calculates distance so we can know when orc needs to change what cell its going towards
	if (m_orcState != OrcState::DIE)
	{
		if ((m_orc.getPosition().x > nextCoordinates.x) && m_orcState == OrcState::WALKING)
		{
			m_orcDirection = Direction::LEFT;
			m_orc.setScale(-3, 3);
		}
		else if (m_orcState == OrcState::WALKING)
		{
			m_orcDirection = Direction::RIGHT;
			m_orc.setScale(3, 3);
		}
		if (m_orcState != OrcState::ATTACKING)//if attacking dont move
			m_orc.move(m_moveNormal);

		if (distance < 10)//orc has reached next cell
		{

			if (movePath.size() == 1)
			{
				m_orcState = OrcState::ATTACKING; //orc is has reached destination
			}
			if (movePath.size() >= 2)
			{
				movePath.pop_back();//remove cell from vector
				nextCell = movePath.back();//set next cell to go to
			}

		}
		if (m_orcHealthSystem.getHealth() <= 0)
		{
			m_orcState = OrcState::DIE;
			m_col = 0;
		}
	}

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
	m_holder.acquire("orcAttackOne", thor::Resources::fromFile<sf::Texture>("ASSETS/IMAGES/Orc/Orc/Orc-Attack01.png"));
	m_holder.acquire("orcDeath", thor::Resources::fromFile<sf::Texture>("ASSETS/IMAGES/Orc/Orc/Orc-Death.png"));
	m_orc.setTexture(m_holder["OrcSpriteIdle"]);

	m_orc.setTextureRect(sf::IntRect(0, 0, m_frameSize, m_frameSize));

	m_orc.setOrigin(m_frameSize / 2, m_frameSize / 2);
	m_orc.setScale(3, 3);
	m_orc.setPosition(1000, 200);

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
		if ((m_col >= m_walkFrames && m_orcState == OrcState::WALKING) || (m_col >= m_idleFrames && m_orcState == OrcState::IDLE) || (m_col >= m_idleFrames && m_orcState == OrcState::ATTACKING))//resets column if exceeded frames of that row
		{
			m_col = 0;
		}
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
		if (m_orcState == OrcState::ATTACKING)
		{
			m_orc.setTexture(m_holder["orcAttackOne"]);
			m_orc.setTextureRect(sf::IntRect((m_col * 100), (m_idleRow * 100), m_frameSize, m_frameSize));
		}
		if (m_orcState == OrcState::DIE)
		{
			m_orc.setTexture(m_holder["orcDeath"]);
			m_orc.setTextureRect(sf::IntRect((m_col * 100), (m_idleRow * 100), m_frameSize, m_frameSize));
			if (m_col > 3)
				respawn();
		}
		m_col++;
		m_frameTimer = 0;
	}
}

void Orc::gridToCoordinate()//gets center of grid for orc to move towards
{
	int row = nextCell / 10;
	int col = nextCell % 10;
	nextCoordinates = sf::Vector2f((col * 140) + 70, (row * 80) + 40);//the coordinates for orc to travel to (centre of cell)
}

void Orc::respawn()
{
	m_deaths++;
<<<<<<< HEAD
	m_orc.setPosition(800, 200);
=======
	m_orc.setPosition(1000, 200);
>>>>>>> obstacleCollision
	m_orcHealthSystem.setHealth(m_orcHealthSystem.getMaxHealth());//sets orc back to max hp
	m_orcState = OrcState::IDLE;
	if (m_speed > 2)
		m_damage = m_damage + 5;
	else 
		m_speed = m_speed + 0.2;
	std::cout << "\n\nrespawn stats: \n VVVVVVVVVV \nspeed: " << m_speed << "\ndamage: " << m_damage;
}

int Orc::getDeaths()
{
	return m_deaths;
}

int Orc::isAttackReady()
{
	if (m_orcState == OrcState::ATTACKING && m_damageTimer>m_damageInterval)
	{
		m_damageTimer = 0;
		return m_damage;//returns ammount of damage to be done
	}
	return 0;
}