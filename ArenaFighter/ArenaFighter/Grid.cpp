#include "Grid.h"
#include <iostream>
Grid::Grid(int t_gridSize,int t_gridRows,int t_gridCols)
    : m_gridSize(t_gridSize),m_gridCols(t_gridCols),m_gridRows(t_gridRows)
{
	initGrid();
}


void Grid::initGrid()
{
    for (int i = 0; i < 100 ; i++)
    {
        cells.emplace_back(i,m_gridRows,m_gridCols);
    }

}
