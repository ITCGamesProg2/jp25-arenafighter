#include "LevelData.h"

LevelData::LevelData(thor::ResourceHolder<sf::Texture, std::string>& t_holder) : m_holder(t_holder), 
m_levelData
	{{
	{{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8}},
	{{3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4}}
	}}
	
{
	
}

void LevelData::initLevel()
{
	m_holder.acquire("tileMap", thor::Resources::fromFile<sf::Texture>("ASSETS/IMAGES/Dungeon_Tileset.png"));
	const sf::Texture& texture = m_holder["tileMap"];
	for (int i = 0; i < m_NO_OF_ROWS; i++)
	{
		for (int j = 0; j < m_NO_OF_COLS; j++)
		{
			m_levelSpriteRectangles[i][j].setSize(sf::Vector2f{ 16,16 });

			if (m_levelData[i][j] == 0) // Top row middle tiles
			{
				m_levelSpriteRectangles[i][j].setTexture(&texture);
				m_levelSpriteRectangles[i][j].setTextureRect(sf::IntRect{ 16,0,16,16 });
				m_levelSpriteRectangles[i][j].setScale(2.0, 2.0);
				m_levelSpriteRectangles[i][j].setPosition(32 * j, 32 * i);
			}
			if (m_levelData[i][j] == 1) // Top Left Corner
			{
				m_levelSpriteRectangles[i][j].setTexture(&texture);
				m_levelSpriteRectangles[i][j].setTextureRect(sf::IntRect{ 0,0,16,16 });
				m_levelSpriteRectangles[i][j].setScale(2.0, 2.0);
				m_levelSpriteRectangles[i][j].setPosition(32 * j, 32 * i);
			}
			if (m_levelData[i][j] == 2) // Top Right Corner
			{
				m_levelSpriteRectangles[i][j].setTexture(&texture);
				m_levelSpriteRectangles[i][j].setTextureRect(sf::IntRect{ 80,0,16,16 });
				m_levelSpriteRectangles[i][j].setScale(2.0, 2.0);
				m_levelSpriteRectangles[i][j].setPosition(32 * j, 32 * i);
			}
			if (m_levelData[i][j] == 3) // Bottom left corner
			{
				m_levelSpriteRectangles[i][j].setTexture(&texture);
				m_levelSpriteRectangles[i][j].setTextureRect(sf::IntRect{ 0,64,16,16 });
				m_levelSpriteRectangles[i][j].setScale(2.0, 2.0);
				m_levelSpriteRectangles[i][j].setPosition(32 * j, 32 * i);
			}
			if (m_levelData[i][j] == 4) // Bottom Right Corner
			{
				m_levelSpriteRectangles[i][j].setTexture(&texture);
				m_levelSpriteRectangles[i][j].setTextureRect(sf::IntRect{ 80,64,16,16 });
				m_levelSpriteRectangles[i][j].setScale(2.0, 2.0);
				m_levelSpriteRectangles[i][j].setPosition(32 * j, 32 * i);
			}
			if (m_levelData[i][j] == 5) // Bottom row middle tiles
			{
				m_levelSpriteRectangles[i][j].setTexture(&texture);
				m_levelSpriteRectangles[i][j].setTextureRect(sf::IntRect{ 16,64,16,16 });
				m_levelSpriteRectangles[i][j].setScale(2.0, 2.0);
				m_levelSpriteRectangles[i][j].setPosition(32 * j, 32 * i);
			}
			if (m_levelData[i][j] == 6) // Floor Tiles
			{
				m_levelSpriteRectangles[i][j].setTexture(&texture);
				m_levelSpriteRectangles[i][j].setTextureRect(sf::IntRect{ 32,32,16,16 });
				m_levelSpriteRectangles[i][j].setScale(2.0, 2.0);
				m_levelSpriteRectangles[i][j].setPosition(32 * j, 32 * i);
			}
			if (m_levelData[i][j] == 7) // Left Wall middle tiles
			{
				m_levelSpriteRectangles[i][j].setTexture(&texture);
				m_levelSpriteRectangles[i][j].setTextureRect(sf::IntRect{ 0,16,16,16 });
				m_levelSpriteRectangles[i][j].setScale(2.0, 2.0);
				m_levelSpriteRectangles[i][j].setPosition(32 * j, 32 * i);
			}
			if (m_levelData[i][j] == 8) // Right wall middle tiles
			{
				m_levelSpriteRectangles[i][j].setTexture(&texture);
				m_levelSpriteRectangles[i][j].setTextureRect(sf::IntRect{ 80,0,16,16 });
				m_levelSpriteRectangles[i][j].setScale(2.0, 2.0);
				m_levelSpriteRectangles[i][j].setPosition(32 * j, 32 * i);
			}
		}
	}
}

void LevelData::renderLevel(sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_NO_OF_ROWS; i++)
	{
		for (int j = 0; j < m_NO_OF_COLS; j++)
		{
			t_window.draw(m_levelSpriteRectangles[i][j]);
		}
	}
}
