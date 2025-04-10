#pragma once
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include <queue>
class Grid
{
public:
	Grid(int t_gridSize,int t_gridRows,int t_gridCols, std::vector<sf::Sprite>& t_obstacleSprites);

	void markGrids();

	std::vector<int> breadthFirst(int t_startCellId, int t_destCellId);

	std::vector<sf::Sprite>& m_obstacleSprites;
	int coordinateToGrid(sf::Vector2f);
private:
	void initGrid();
	int m_gridSize;
	int m_gridRows;
	int m_gridCols;

	int m_cellWidth = 140;
	int m_cellHeight = 80;
	std::vector<Cell> cells;
};