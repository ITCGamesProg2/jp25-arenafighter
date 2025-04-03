#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class SpatialPartitionGrid
{
private:
	float m_cellWidth;
	float m_cellHeight;
	std::map < std::pair<int, int>, std::vector<sf::FloatRect*>> grid;


public:
	
	SpatialPartitionGrid(float cellWidth, float cellHeight) : m_cellWidth(cellWidth), m_cellHeight(cellHeight) {}

	/// <summary>
	/// This function takes a game objects position as a reference and uses this to calculate which cell in the grid
	/// the object is in
	/// </summary>
	/// <param name="t_position"></param>
	/// <returns>an std::pair representing the row and column of the grid the object is in</returns>
	std::pair<int, int> getCellCoordinates(const sf::Vector2f& t_position);

	/// <summary>
	/// This function will take a reference to agame objects bounding box and insert it into the grid
	/// This is used for efficient collision detection
	/// </summary>
	/// <param name="t_boundingBox"></param>
	void insertGameObjectIntoGrid(sf::FloatRect* t_boundingBox);

	/// <summary>
	/// This funtion accepts the bounding box of a game object and then checks a 3x3 area around this box for other objects
	/// </summary>
	/// <param name="t_boundingBox"></param>
	/// <returns> A vector containing the bounding boxes of any object near the object the function was called on</returns>
	std::vector<sf::FloatRect> getNearbyObjects(const sf::FloatRect* t_boundingBox);
	
	 
	void drawGrid(sf::RenderWindow& t_window, const sf::FloatRect* t_playerBounds = nullptr, bool t_debugMode = false);


	void clearGrid();
};

