#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>

enum class PlayerState
{
	IDLE,		// 0
	WALKING,	// 1
	ATTACKING	// 2
};

enum class Direction
{
	LEFT,		// 0
	RIGHT		// 1
};

class Player : public GameObject
{
public:
	Player(thor::ResourceHolder <sf::Texture, std::string>& t_holder);

	sf::RectangleShape m_hitbox;

	void update(double dt);
	void render(sf::RenderWindow& window, bool t_debugMode);
	void handleKeyInput();
	sf::FloatRect getBounds() const override;
	sf::Vector2f getOrigin();
	sf::Vector2f getPosition() const override;


	/// <summary>
	/// Checks if the player is in the attacking state
	/// </summary>
	/// <returns>True is player is attacking otherwise false</returns>
	bool isAttacking();
	bool updateGrid(int);
private:
	void initSprites();
	void animate(double dt);
	sf::Sprite m_player;
	
	double m_speed{ 2.0 };

	int m_frameSize = 100;
	double m_frameTimer = 0.0;
	double m_timePerFrame = 0.1;
	int currentFrame = 0;
	int m_col = 0;
	int m_currentGrid = -1;

	int m_walkFrames = 8;
	int m_idleFrames = 6;
	int m_walkRow = 0;
	int m_idleRow = 0;

	//int m_playerState = 0; //0: idle   1: moving
	PlayerState m_playerState;
	Direction m_playerDirection;
	thor::ResourceHolder<sf::Texture, std::string>& m_holder;
};
