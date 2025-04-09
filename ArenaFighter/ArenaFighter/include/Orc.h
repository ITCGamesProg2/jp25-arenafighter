#pragma once
#include "GameObject.h"
#include "HealthSystem.h"
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>

enum class OrcState
{
	IDLE,		// 0
	WALKING,	// 1
	ATTACKING,	// 2
	DIE
};



class Orc : public GameObject
{
public:
	Orc(thor::ResourceHolder <sf::Texture, std::string>& t_holder);

	sf::RectangleShape m_hitbox;
	HealthSystem m_orcHealthSystem;
	bool hasTakenAttackDamage = false;
	void update(double dt);
	void render(sf::RenderWindow& window,bool debugMode);

	sf::FloatRect getBounds() const override;
	sf::Vector2f getPosition() const override; 

	/// <summary>
	/// Positions the healthbox over the orc, updates health bar visuals to reflect changes in health
	/// </summary>
	void updtateHealthbar();

	void setMovePath(std::vector<int>);

	int getDeaths();
	int isAttackReady();
private:
	void gridToCoordinate();
	void initSprites();
	void animate(double dt);
	void respawn();

	sf::Sprite m_orc;
	
	sf::Vector2f m_moveNormal;

	int nextCell;
	sf::Vector2f nextCoordinates;

	int m_damage = 10;
	float m_damageTimer = 0.0f;
	float m_damageInterval = 0.6f;

	int m_frameSize = 100;
	double m_frameTimer = 0.0;
	double m_timePerFrame = 0.1;
	int currentFrame = 0;
	int m_col = 0;

	int m_walkFrames = 8;
	int m_idleFrames = 6;
	int m_walkRow = 0;
	int m_idleRow = 0;

	int m_deaths = 0;

	float m_speed = 0.5;

	std::vector<int> movePath;
	Direction m_orcDirection;

	OrcState m_orcState = OrcState::IDLE; //0: idle   1: moving

	sf::RectangleShape m_healthBar;
	sf::RectangleShape m_healthBarBack;

	thor::ResourceHolder<sf::Texture, std::string>& m_holder;
	
};
