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

void Grid::markGrids(sf::RectangleShape& t_rect1, sf::RectangleShape& t_rect2, sf::RectangleShape& t_rect3)
{
    for (int i = 0; i < 100; i++)
    {
        sf::FloatRect cellRect((i % 10) * m_cellWidth, ((i / 10) * m_cellHeight), m_cellWidth, m_cellHeight);//calculates a rectangle to compare with object

        if (cellRect.intersects(t_rect1.getGlobalBounds()) || cellRect.intersects(t_rect2.getGlobalBounds()) || cellRect.intersects(t_rect3.getGlobalBounds()))
        {//need to change to a vector of objects/shapes for when obstacles are fully added
            cells[i].setMarked(true);
        }
    }
}

std::vector<int> Grid::breadthFirst(int t_startCellId, int t_destCellId)
{
    std::queue<int> cellQueue;

    bool goalReached = false;
    cells[t_startCellId].setMarked(true);

    std::vector<int> previousCell;//stores path

    cellQueue.push(t_startCellId);

    while (cellQueue.size() > 0 && !goalReached)
    {
        int currentCell = cellQueue.front();
        std::vector<int> neighbours = cells[currentCell].getNeighbours(); //creates a vector of neibhbours id's
        for (int neighbourID : neighbours) 
        {  // Loop through neighbour IDs

            if (neighbourID == t_destCellId)
            {
                goalReached = true;
                previousCell.push_back(currentCell);
            }

            else if (!cells[neighbourID].isMarked())
            {
                cells[neighbourID].setMarked(true);
                cellQueue.push(neighbourID);
            }
        }
        cellQueue.pop();//removes cell from front of queue
    }


    return previousCell;
}
