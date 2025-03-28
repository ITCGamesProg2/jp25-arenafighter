#include "SpatialPartitionGrid.h"

SpatialPartitionGrid::SpatialPartitionGrid()
{
	m_cell.setSize(sf::Vector2f(CELL_WIDTH, CELL_HEIGHT));
	m_cell.setFillColor(sf::Color(100, 100, 250, 150));
	m_cell.setOutlineThickness(2.0);
	m_cell.setOutlineColor(sf::Color::White);

	m_cellTester.setSize(sf::Vector2f(50, 50));
	m_cellTester.setFillColor(sf::Color::Red);
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
	t_window.draw(m_cellTester);
}

void SpatialPartitionGrid::moveTester()
{
	m_cellTester.move(m_testerMoveVec);

	if (m_cellTester.getPosition().x > 1390 || m_cellTester.getPosition().x < 10)
	{
		m_testerMoveVec.x *= -1;
	}
	else if (m_cellTester.getPosition().y < 10 || m_cellTester.getPosition().y > 790)
	{
		m_testerMoveVec.y *= -1;
	}
}

void SpatialPartitionGrid::testCells()
{
	for (int i = 0; i < NUM_CELLS_X; i++)
	{
		for (int j = 0; j < NUM_CELLS_Y; j++)
		{
			if (m_cell.getGlobalBounds().contains(m_cellTester.getPosition()))
			{
				m_cell.setFillColor(sf::Color::Red);
			}
			else
			{
				m_cell.setFillColor(sf::Color(100, 100, 250, 150));

			}
		}
	}
	
}
