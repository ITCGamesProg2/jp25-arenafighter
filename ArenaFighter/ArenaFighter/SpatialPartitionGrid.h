#pragma once

#include <SFML/Graphics.hpp>

class SpatialPartitionGrid
{
public:
	SpatialPartitionGrid();

	void renderGrid(sf::RenderWindow& t_window);

/// <summary>
/// Moves the tester around the grid area to test each cell to see if it works correctly
/// </summary>
	void moveTester();
	void testCells();

private:
	const int CELL_WIDTH = 140;
	const int CELL_HEIGHT = 80;

	const int NUM_CELLS_X = 1400 / CELL_WIDTH;
	const int NUM_CELLS_Y = 800 / CELL_HEIGHT;
	
	sf::RectangleShape m_cell;

	sf::RectangleShape m_cellTester; 
	sf::Vector2f m_testerMoveVec = { 20, 10 };
};

