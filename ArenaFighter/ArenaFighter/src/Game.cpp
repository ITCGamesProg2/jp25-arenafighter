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
	m_window{ sf::VideoMode{ 1408U, 800U, 32U }, "SFML Game" }
	, m_player(m_holder), m_exitGame{false}, m_collisionLine{sf::Lines, 2}, m_orc(m_holder), m_searchGrid(100,10,10,m_obstacleSprites), m_level(m_holder), m_pickup(m_holder)
{
	setupTest(); // load texture
	m_searchGrid.markGrids();

	setupText();

	std::vector<int> vector = m_searchGrid.breadthFirst(3, 3);//calls search function with start and destination

	std::cout << "\n\n breath search: "; //output result
	for (int i : vector) {
		std::cout << i << " ";
	}
	int currentLevel = 1; // Will generate an exception if level loading fails. 
	try
	{
		LevelLoader::load(currentLevel, m_levelData);
	}
	catch (std::exception& e)
	{
		std::cout << "Level Loading failure." << std::endl;
		std::cout << e.what() << std::endl;
		throw e;
	}
	m_holder.acquire("obstacle", thor::Resources::fromFile<sf::Texture>("ASSETS/IMAGES/woodenBox.png"));
	m_obstacleTexture = m_holder["obstacle"];
	generateObstacles();
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


			if (m_player.updateGrid(m_searchGrid.coordinateToGrid(m_player.getPosition()))) //if player has moved to a new grid
			{//give orc new move path VVVV
				m_searchGrid.markGrids();//mark grid with objects
				m_orc.setMovePath(m_searchGrid.breadthFirst(m_searchGrid.coordinateToGrid(m_orc.getPosition()), m_searchGrid.coordinateToGrid(m_player.getPosition())));
			}

			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
			m_player.update(static_cast<double>(timePerFrame.asSeconds()));
			m_orc.update(static_cast<double>(timePerFrame.asSeconds()));
			if (m_score < m_orc.getDeaths())
			{ //calls breadth first search again as orc has respawned elsewhere
				m_score = m_orc.getDeaths();
				m_searchGrid.markGrids();//mark grid with objects
				m_orc.setMovePath(m_searchGrid.breadthFirst(m_searchGrid.coordinateToGrid(m_orc.getPosition()), m_searchGrid.coordinateToGrid(m_player.getPosition())));
			}
			m_scoreText.setString("Score: " + std::to_string(m_score));
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
		if (sf::Event::KeyReleased == newEvent.type) //user released a key
		{
			processKeyRelease(newEvent);
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
	if (sf::Keyboard::M == t_event.key.code)
	{
		m_debugMode = !m_debugMode;
	}
	
	
}

void Game::processKeyRelease(sf::Event t_event)
{
	if (sf::Keyboard::Space == t_event.key.code)
	{
		m_orc.hasTakenAttackDamage = false;
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
	m_grid.insertGameObjectIntoGrid(&m_player.getBounds());
	m_grid.insertGameObjectIntoGrid(&m_orc.getBounds());
	m_grid.insertGameObjectIntoGrid(&m_pickup.getHitbox());
	

	m_player.keepPlayerInBounds();
	testCollisions();
	combatCollisions();
	pickupCollisions();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{

	m_window.clear(sf::Color::Black);
	m_window.draw(m_backgroundSprite);
	m_level.renderLevel(m_window);
	m_grid.drawGrid(m_window, &m_player.getBounds(), m_debugMode);
	m_pickup.renderickups(m_window, m_debugMode);
	

	m_player.render(m_window, m_debugMode);
	
	m_orc.render(m_window, m_debugMode);
	m_window.draw(m_scoreText);
	for (sf::Sprite sprite : m_obstacleSprites) //goes through wall sprites, drawing each one
	{
		m_window.draw(sprite);
	}
	if (m_debugMode)
	{
		if (m_collisonPresent)
		{
			m_window.draw(m_collisionLine);
		}
	}
	m_window.display();
	
}



/// <summary>
/// Set up the obstacles to check grid collision
/// </summary>
void Game::setupTest()
{
	m_collisionLine[0] = m_player.getOrigin();
	m_collisionLine[1] = m_player.getOrigin();
	

	m_holder.acquire("backImage", thor::Resources::fromFile<sf::Texture>("ASSETS/IMAGES/floorTiles.png"));
	m_backgroundSprite.setTexture(m_holder["backImage"]);
	m_backgroundSprite.setPosition({ 0,0 });

	m_level.initLevel();
	
}

void Game::testCollisions()
{
	std::vector<sf::FloatRect> nearbyObjects = m_grid.getNearbyObjects(&m_player.getBounds());

	m_collisionLine[0] = m_player.getPosition();
	m_collisonPresent = false;
	for (auto &object : nearbyObjects)
	{
		if (object.intersects(m_player.getBounds()))
		{
			m_collisonPresent = true;
			// Check which obstacle is being collided with and change its color
			if (object == m_orc.getBounds())
			{
				m_collisionLine[1] = m_orc.getPosition();
			}
			else if (object == m_pickup.getHitbox())
			{
				m_collisionLine[1] = m_pickup.returnHitboxPosition();
			}
			
		}
		
	}
	
}



void Game::combatCollisions()
{
	std::vector<sf::FloatRect> nearbyObjectsPlayer = m_grid.getNearbyObjects(&m_player.getBounds());

	for (auto& object : nearbyObjectsPlayer)
	{
		if (object == m_orc.getBounds() && m_player.isAttacking())
		{
			if (object.intersects(m_player.getBounds()))
			{
				if (!m_orc.hasTakenAttackDamage)
				{
					m_orc.m_orcHealthSystem.takeDamage(10);
					m_orc.hasTakenAttackDamage = true;
					std::cout << m_orc.m_orcHealthSystem.getHealth() << "\n";
				}
			}
		}
		
	}
}


void Game::setupText()
{
	m_fontHolder.acquire("scoreFont", thor::Resources::fromFile<sf::Font>("ASSETS/FONTS/PixelPurl.ttf"));
	m_scoreText.setFont(m_fontHolder["scoreFont"]);
	m_scoreText.setPosition(50, 30);
	m_scoreText.setCharacterSize(34);
	m_scoreText.setFillColor(sf::Color::White);
}

void Game::pickupCollisions()
{
	if (m_pickup.getHitbox().intersects(m_player.getBounds()) && m_pickup.getType() == PickupType::POTION)
	{
		m_player.m_playerHealthSystem.increaseHealth();
		m_pickup.initPickups();
	}
	else if (m_pickup.getHitbox().intersects(m_player.getBounds()) && m_pickup.getType() == PickupType::POISON)
	{
		m_player.m_playerHealthSystem.takeDamage(20);
		m_pickup.initPickups();
	}
	
}


void Game::generateObstacles() 
{
	std::cout << "generating";
	// Replace the ? With the actual values for the wall image 
	sf::IntRect wallRect(0, 0, 424, 408);
	// Create the Walls 
	for (auto const& obstacle : m_levelData.m_obstacles)
	{
		std::cout << "created obstacle";
		sf::Sprite sprite;
		sprite.setTexture(m_obstacleTexture);
		sprite.setTextureRect(wallRect);
		sprite.setOrigin(wallRect.width / 2.0, wallRect.height / 2.0);
		sprite.setPosition(obstacle.m_position);
		sprite.setRotation(obstacle.m_rotation);
		sprite.setScale(0.14,0.14);
		m_obstacleSprites.push_back(sprite);
	}
}