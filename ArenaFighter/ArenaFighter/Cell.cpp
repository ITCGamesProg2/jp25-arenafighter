#include "Cell.h"
#include <iostream>
Cell::Cell(int t_cellID, int t_gridRows,int t_gridCols)
	: m_cellID(t_cellID),m_gridRows(t_gridRows),m_gridCols(t_gridCols)
{
	initCell();
}


void Cell::initCell()
{
	//std::cout << "\ncell created ID:" << m_cellID;
	setNeighbours();
}

void Cell::setNeighbours()
{
    int row = m_cellID / m_gridRows;
    int col = m_cellID % m_gridCols;
    int rowOffset[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
    int colOffset[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    for (int i = 0; i < 8; i++)
    {

        int newRow = row + rowOffset[i];
        int newCol = col + colOffset[i];
        if (newRow >= 0 && newRow < m_gridRows && newCol >= 0 && newCol < m_gridCols) 
        {
            m_neighbours.emplace_back((newRow * m_gridCols + newCol));
        }
    }
}

std::vector<int>& Cell::getNeighbours()
{
    return m_neighbours;
}

bool Cell::isMarked() const // returns the member variable m_marked;
{
    return m_marked;
}

void Cell::setMarked(bool t_val) // setter method to set the value of member m_marked
{
    m_marked = t_val;
}
