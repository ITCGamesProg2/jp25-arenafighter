#pragma once

#include <SFML/Graphics.hpp>

class SpatialPartitionGrid
{
public:
	SpatialPartitionGrid();
	void renderGrid(sf::RenderWindow& t_window);

private:
	const int CELL_WIDTH = 140;
	const int CELL_HEIGHT = 80;

	const int NUM_CELLS_X = 1400 / CELL_WIDTH;
	const int NUM_CELLS_Y = 800 / CELL_HEIGHT;
	
	sf::RectangleShape m_cell;
};

