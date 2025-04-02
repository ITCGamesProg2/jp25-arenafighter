#pragma once
#include <SFML/Graphics.hpp>
#include "Cell.h"
class Grid
{
public:
	Grid(int t_gridSize);



private:
	void initGrid();
	int m_gridSize;
	std::vector<Cell> cells;
};