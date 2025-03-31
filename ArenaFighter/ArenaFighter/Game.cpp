/// <summary>
/// author Conor Foley March 2025
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1400U, 800U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupTest(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
#ifdef _DEBUG
			render(); // want to debug drawing while stepping through code
#endif // _DEBUG

		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::W == t_event.key.code)
	{
		m_playerPosition.y -= m_playerSpeed;
	}
	if (sf::Keyboard::S == t_event.key.code)
	{
		m_playerPosition.y += m_playerSpeed;
	}
	if (sf::Keyboard::A == t_event.key.code)
	{
		m_playerPosition.x -= m_playerSpeed;
	}
	if (sf::Keyboard::D == t_event.key.code)
	{
		m_playerPosition.x += m_playerSpeed;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (t_deltaTime.asMilliseconds() != 16)
	{
		std::cout << "time warp" << std::endl; // expecting 60 fps of action
	}
	if (m_exitGame)
	{
		m_grid.clearGrid();
		m_window.close();
	}
	m_grid.clearGrid();
	m_grid.insertGameObjectIntoGrid(&m_obstacleOne.getGlobalBounds());
	m_grid.insertGameObjectIntoGrid(&m_obstacleTwo.getGlobalBounds());
	m_grid.insertGameObjectIntoGrid(&m_obstacleThree.getGlobalBounds());
	m_grid.insertGameObjectIntoGrid(&m_playerShape.getGlobalBounds());

	m_playerShape.setPosition(m_playerPosition);

	testCollisions();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_grid.drawGrid(m_window, &m_playerShape.getGlobalBounds());
	m_window.draw(m_obstacleOne);
	m_window.draw(m_obstacleTwo);
	m_window.draw(m_obstacleThree);
	m_window.draw(m_playerShape);
	m_window.display();
	
}



/// <summary>
/// Set up the obstacles to check grid collision
/// </summary>
void Game::setupTest()
{
	m_obstacleOne.setSize(sf::Vector2f(50.0f, 50.0f));
	m_obstacleTwo.setSize(sf::Vector2f(50.0f, 50.0f));
	m_obstacleThree.setSize(sf::Vector2f(50.0f, 50.0f));
	m_playerShape.setSize(sf::Vector2f(50.0f, 50.0f));

	m_obstacleOne.setPosition(200, 200);
	m_obstacleTwo.setPosition(400, 400);
	m_obstacleThree.setPosition(600, 600);
	m_playerShape.setPosition(100, 100);

	m_obstacleOne.setFillColor(sf::Color::Red);
	m_obstacleTwo.setFillColor(sf::Color::Red);
	m_obstacleThree.setFillColor(sf::Color::Red);
	m_playerShape.setFillColor(sf::Color::Green);

	m_playerPosition = m_playerShape.getPosition();
}

void Game::testCollisions()
{
	std::vector<sf::FloatRect> nearbyObjects = m_grid.getNearbyObjects(&m_playerShape.getGlobalBounds());

	resetObstacleColours();

	for (auto &object : nearbyObjects)
	{
		if (object.intersects(m_playerShape.getGlobalBounds()))
		{
			// Check which obstacle is being collided with and change its color
			if (object == m_obstacleOne.getGlobalBounds())
			{
				m_obstacleOne.setFillColor(sf::Color::Magenta);
			}
			else if (object == m_obstacleTwo.getGlobalBounds())
			{
				m_obstacleTwo.setFillColor(sf::Color::Magenta);
			}
			else if (object == m_obstacleThree.getGlobalBounds())
			{
				m_obstacleThree.setFillColor(sf::Color::Magenta);
			}
		}
	}
}

void Game::resetObstacleColours()
{
	m_obstacleOne.setFillColor(sf::Color::Red);
	m_obstacleTwo.setFillColor(sf::Color::Red);
	m_obstacleThree.setFillColor(sf::Color::Red);
}
