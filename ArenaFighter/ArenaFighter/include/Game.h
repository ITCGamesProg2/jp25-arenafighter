/// <summary>
/// author Pete Lowe May 2022
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include "Player.h"
#include "SpatialPartitionGrid.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	// This is purely for testing, will remove once I'm happy with how the grid and collisions work
	void setupTest();
	void testCollisions();
	void resetObstacleColours();


	thor::ResourceHolder<sf::Texture, std::string> m_holder;
	Player m_player;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game
	SpatialPartitionGrid m_grid{ 140, 80 };

	sf::RectangleShape m_obstacleOne;
	sf::RectangleShape m_obstacleTwo;
	sf::RectangleShape m_obstacleThree;
	sf::RectangleShape m_playerShape;
	float m_playerSpeed = 5.0f;
	sf::Vector2f m_playerPosition;


	bool m_debugMode = false;
};

#endif // !GAME_HPP

