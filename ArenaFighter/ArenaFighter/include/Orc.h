#pragma once
#include "GameObject.h"
#include "HealthSystem.h"
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>

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
	/// Positions the healthbox over the orc, updates health bar visuals
	/// </summary>
	void updtateHealthbar();

private:
	void initSprites();
	void animate(double dt);
	sf::Sprite m_orc;
	
	double m_speed{ 2.0 };

	int m_frameSize = 100;
	double m_frameTimer = 0.0;
	double m_timePerFrame = 0.1;
	int currentFrame = 0;
	int m_col = 0;

	int m_walkFrames = 8;
	int m_idleFrames = 6;
	int m_walkRow = 0;
	int m_idleRow = 0;

	int m_orcState = 0; //0: idle   1: moving

	sf::RectangleShape m_healthBar;
	sf::RectangleShape m_healthBarBack;

	thor::ResourceHolder<sf::Texture, std::string>& m_holder;
	
};
