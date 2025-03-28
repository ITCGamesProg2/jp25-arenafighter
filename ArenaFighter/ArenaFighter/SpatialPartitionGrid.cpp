#include "SpatialPartitionGrid.h"

SpatialPartitionGrid::SpatialPartitionGrid()
{
	m_cell.setSize(sf::Vector2f(CELL_WIDTH, CELL_HEIGHT));
	m_cell.setFillColor(sf::Color(100, 100, 250, 150));
}

void SpatialPartitionGrid::renderGrid(sf::RenderWindow& t_window)
{
	for (int i = 0; i < NUM_CELLS_X; i++)
	{
		for (int j = 0; j < NUM_CELLS_Y; j++)
		{
			m_cell.setPosition(i * CELL_WIDTH, j * CELL_HEIGHT);
			t_window.draw(m_cell);
		}
	}
}
