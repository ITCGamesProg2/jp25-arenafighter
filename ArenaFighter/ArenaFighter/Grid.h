#pragma once
#include <SFML/Graphics.hpp>
#include "Cell.h"
class Grid
{
public:
	Grid(int t_gridSize,int t_gridRows,int t_gridCols);

	void markGrids(sf::RectangleShape& t_rect1, sf::RectangleShape& t_rect2, sf::RectangleShape& t_rect3);

private:
	void initGrid();
	int m_gridSize;
	int m_gridRows;
	int m_gridCols;

	sf::RectangleShape m_rect1;
	sf::RectangleShape m_rect2;
	sf::RectangleShape m_rect3;

	int m_cellWidth = 100;
	int m_cellHeight = 100;
	std::vector<Cell> cells;
};