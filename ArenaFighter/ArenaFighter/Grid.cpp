#include "Grid.h"
#include <iostream>
Grid::Grid(int t_gridSize)
    : m_gridSize(t_gridSize)
{
	initGrid();
}


void Grid::initGrid()
{
    for (int i = 0; i < 100 ; i++)
    {
        cells.emplace_back(i);
    }

}
