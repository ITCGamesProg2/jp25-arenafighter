#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include <array>

class LevelData
{
public:
	LevelData(thor::ResourceHolder <sf::Texture, std::string>& t_holder);


	void initLevel();
	/// <summary>
	/// Populates the rectangle shape vector with the correct textures, assigns positions and scale
	/// </summary>
	/// <param name="t_window">A reference to the game window</param>
	void renderLevel(sf::RenderWindow& t_window);

private:
	thor::ResourceHolder<sf::Texture, std::string>& m_holder;

	static const int m_NO_OF_COLS = 44;
	static const int m_NO_OF_ROWS = 25;

	std::array<std::array<int, m_NO_OF_COLS>, m_NO_OF_ROWS> m_levelData;

	sf::RectangleShape m_levelSpriteRectangles[m_NO_OF_ROWS][m_NO_OF_COLS];

	std::vector<sf::Sprite> m_obstacles;
};