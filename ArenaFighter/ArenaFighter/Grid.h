#pragma once
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include <queue>
class Grid
{
public:
	Grid(int t_gridSize,int t_gridRows,int t_gridCols);

	void markGrids(sf::RectangleShape& t_rect1, sf::RectangleShape& t_rect2, sf::RectangleShape& t_rect3);

	std::vector<int> breadthFirst(int t_startCellId, int t_destCellId);


	int coordinateToGrid(sf::Vector2f);
private:
	void initGrid();
	int m_gridSize;
	int m_gridRows;
	int m_gridCols;


	sf::RectangleShape m_rect1;
	sf::RectangleShape m_rect2;
	sf::RectangleShape m_rect3;



	int m_cellWidth = 140;
	int m_cellHeight = 80;
	std::vector<Cell> cells;
};