#pragma once
#include <SFML/Graphics.hpp>
#include "Cell.h"
class Grid
{
public:
	Grid(int t_gridSize,int t_gridRows,int t_gridCols);



private:
	void initGrid();
	int m_gridSize;
	int m_gridRows;
	int m_gridCols;
	std::vector<Cell> cells;
};