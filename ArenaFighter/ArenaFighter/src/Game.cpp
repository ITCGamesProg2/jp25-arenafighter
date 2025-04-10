/// <summary>
/// author Conor Foley, Jack Kane March 2025
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

	int currentLevel = 1; 
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

	for (auto hitbox : m_obstacleHitboxes)
	{
		m_grid.insertGameObjectIntoGrid(&hitbox.getGlobalBounds());
	}

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
				//generates new move path for orc ^^^
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
			m_scoreText.setString("Score: " + std::to_string(m_score));//score text
			m_highScoreText.setString("HighScore: " + std::to_string(m_highScore));//score text
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
	if (sf::Keyboard::R == t_event.key.code && m_gameOver)
	{
		m_gameOver = false;
		restartGame();
		m_score = 0;
		std::cout << "restart";
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
	
	if (m_player.isGameOver())
	{
		if (m_score > m_highScore)
			m_highScore = m_score;
		if (!m_gameOver)
		{
			m_gameOverText.setString("Game over\nPress R to play again!\nYour score was: " + std::to_string(m_score) + "\nYour highscore is: "+ std::to_string(m_highScore));
		}
		m_gameOver = true;
	}
	else 
		m_gameOver = false;

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
	if (!m_gameOver)
	{
		m_window.draw(m_backgroundSprite);
		m_level.renderLevel(m_window);
		m_grid.drawGrid(m_window, &m_player.getBounds(), m_debugMode);
		m_pickup.renderickups(m_window, m_debugMode);

		m_player.render(m_window, m_debugMode);

		m_orc.render(m_window, m_debugMode);

		for (sf::Sprite sprite : m_obstacleSprites) //goes through wall sprites, drawing each one
		{
			m_window.draw(sprite);
		}
		if (m_debugMode)
		{
			for (auto hitbox : m_obstacleHitboxes)
			{
				m_window.draw(hitbox);
			}
			if (m_collisonPresent)
			{
				m_window.draw(m_collisionLine);
			}
		}
		m_window.draw(m_scoreText);
		m_window.draw(m_highScoreText);
	}
	else
	{
		m_window.draw(m_gameOverText);
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
	m_grid.m_collisionClock.restart();

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
	for (auto& hitbox : m_obstacleHitboxes)
	{
		if (hitbox.getGlobalBounds().intersects(m_player.getBounds()))
		{
			m_collisonPresent = true;
			m_collisionLine[1] = hitbox.getPosition();
			playerCollisionWithObstacles(hitbox.getGlobalBounds());
		}
	}

	m_grid.m_collisionTime = m_grid.m_collisionClock.getElapsedTime().asMicroseconds();
	m_grid.m_maxCollisionTime = std::max(m_grid.m_maxCollisionTime, m_grid.m_collisionTime);
}



void Game::playerCollisionWithObstacles(const sf::FloatRect& obstacleBounds)
{
	sf::FloatRect playerBounds = m_player.getBounds();
	sf::Vector2f playerPos = m_player.getPosition();

	// Calculate how far into the obstacle the player is
	float overlapLeft = playerBounds.left + playerBounds.width - obstacleBounds.left;
	float overlapRight = obstacleBounds.left + obstacleBounds.width - playerBounds.left;
	float overlapTop = playerBounds.top + playerBounds.height - obstacleBounds.top;
	float overlapBottom = obstacleBounds.top + obstacleBounds.height - playerBounds.top;

	// Checks which overlap is the largest to determine which side the player is coming from 
	bool fromLeft = (overlapLeft < overlapRight);
	bool fromTop = (overlapTop < overlapBottom);
	// Checks the above booleans and sets up how far the player needs to be pushed away to remove them from the obstacle
	float minOverlapX = fromLeft ? overlapLeft : overlapRight; // If coming from left (ie. True), use overlapLeft, if false use overlapRight
	float minOverlapY = fromTop ? overlapTop : overlapBottom; // If coming from top (ie. True), use overlapTop, if false use overlapBottom

	// If horizontal overlap is smaller, resolve the collision along the X-axis (left/right)
	// Else If the vertical overlap is smaller, resolve the collision along the Y-axis (up/down).
	if (minOverlapX < minOverlapY)
	{
		if (fromLeft)
			playerPos.x -= minOverlapX;
		else
			playerPos.x += minOverlapX;
	}
	else
	{
		if (fromTop)
			playerPos.y -= minOverlapY;
		else
			playerPos.y += minOverlapY;
	}

	m_player.setPosition(playerPos);
}

void Game::combatCollisions()
{
	m_player.m_playerHealthSystem.takeDamage(m_orc.isAttackReady());//if orc attack is ready deal damage

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
	m_highScoreText.setFont(m_fontHolder["scoreFont"]);
	m_gameOverText.setFont(m_fontHolder["scoreFont"]);

	m_scoreText.setPosition(50, 30);
	m_highScoreText.setPosition(50, 60);
	m_gameOverText.setPosition(500, 200);

	m_scoreText.setCharacterSize(34);
	m_scoreText.setFillColor(sf::Color::White);


	m_grid.initFontForDebug();

	m_highScoreText.setCharacterSize(34);
	m_highScoreText.setFillColor(sf::Color::White);

	m_gameOverText.setCharacterSize(60);
	m_gameOverText.setFillColor(sf::Color::White);

	m_gameOverText.setString("Game over\nPress R to play again!");


}

void Game::pickupCollisions()
{
	if (m_pickup.getHitbox().intersects(m_player.getBounds()))
	{
		m_pickup.applyPickupEffect();
		if (m_pickup.getType() == PickupType::POISON)
		{
			m_player.m_playerHealthSystem.takeDamage(10);
		}
		else
		{
			m_player.m_playerHealthSystem.increaseHealth();
		}
		m_pickup.initPickups();
	}

	if (m_pickup.getHitbox().intersects(m_orc.getBounds()))
	{
		m_pickup.applyPickupEffect();
		if (m_pickup.getType() == PickupType::POISON)
		{
			m_orc.m_orcHealthSystem.takeDamage(30);
		}
		else
		{
			m_orc.m_orcHealthSystem.increaseHealth();
		}
		m_pickup.initPickups();
	}

}


void Game::generateObstacles() 
{
	sf::IntRect wallRect(0, 0, 424, 408);
	// Create the Walls 
	for (auto const& obstacle : m_levelData.m_obstacles)
	{
		sf::Sprite sprite;
		sprite.setTexture(m_obstacleTexture);
		sprite.setTextureRect(wallRect);
		sprite.setOrigin(wallRect.width / 2.0, wallRect.height / 2.0);
		sprite.setPosition(obstacle.m_position);
		sprite.setRotation(obstacle.m_rotation);
		sprite.setScale(0.14,0.14);
		m_obstacleSprites.push_back(sprite);

		// For the hitbox of each obstacle
		sf::RectangleShape obstacleHitBox;
		obstacleHitBox.setSize({ 60,60 });
		obstacleHitBox.setFillColor(sf::Color::Transparent);
		obstacleHitBox.setOutlineColor(sf::Color::Green);
		obstacleHitBox.setOutlineThickness(1);
		obstacleHitBox.setOrigin(30, 30);
		obstacleHitBox.setPosition(obstacle.m_position);
		obstacleHitBox.setRotation(obstacle.m_rotation);
		m_obstacleHitboxes.push_back(obstacleHitBox);
	}
}

void Game::restartGame()
{
	m_player.respawn();
	m_score = 0;
	m_orc.reset();
}