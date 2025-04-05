#include "Grid.h"
#include <iostream>
Grid::Grid(int t_gridSize,int t_gridRows,int t_gridCols)
    : m_gridSize(t_gridSize),m_gridCols(t_gridCols),m_gridRows(t_gridRows)
{
	initGrid();
}


void Grid::initGrid()
{
    for (int i = 0; i < m_gridSize ; i++)
    {
        cells.emplace_back(i,m_gridRows,m_gridCols);
    }

}

void Grid::markGrids(sf::RectangleShape& t_rect1, sf::RectangleShape& t_rect2, sf::RectangleShape& t_rect3)
{
    for (int i = 0; i < m_gridSize; i++)
    {
        sf::FloatRect cellRect((i % m_gridCols) * m_cellWidth, ((i / m_gridRows) * m_cellHeight), m_cellWidth, m_cellHeight);//calculates a rectangle to compare with object

        if (cellRect.intersects(t_rect1.getGlobalBounds()) || cellRect.intersects(t_rect2.getGlobalBounds()) || cellRect.intersects(t_rect3.getGlobalBounds()))
        {//need to change to a vector of objects/shapes for when obstacles are fully added
            cells[i].setMarked(true);
        }
        else
        {
            cells[i].setMarked(false);
        }
    }
}

std::vector<int> Grid::breadthFirst(int t_startCellId, int t_destCellId)
{
    
    std::queue<int> cellQueue;//the queue of cells that need to be checked
    markGrids(m_rect1, m_rect2, m_rect3);
    bool goalReached = false;//is destination found?
    cells[t_startCellId].setMarked(true);//mark starting cell as we dont need to search it

    std::vector<int> previousCell(m_gridSize);//stores location of previous cells so path can be traced back

    cellQueue.push(t_startCellId);//add starting cell into the queue

    while (cellQueue.size() > 0 && !goalReached)//while there is still an id in queue and destination not reached
    {

        int currentCell = cellQueue.front();//set the current cell to the cell that is to be searched next
        std::vector<int> neighbours = cells[currentCell].getNeighbours(); //creates a vector of neibhbours id's for the current cell


        for (int neighbourID : neighbours) 
        {  // Loop through neighbour IDs

            if (neighbourID == t_destCellId)//if the neighbour is the destination
            {
                goalReached = true;//destination found
                previousCell[neighbourID] = currentCell;//updates the location of the neighbours id to the current cell so it can be traced back later to find the path
            }

            else if (!cells[neighbourID].isMarked())//if cell is not marked and not destination
            {
                cells[neighbourID].setMarked(true);//sets cell to marked as destination is not in cell
                previousCell[neighbourID] = currentCell;//updates the location of the neighbours id to the current cell so it can be traced back later to find the path
                cellQueue.push(neighbourID);//adds neighbour id to the queue so that cell can be checked next
            }
        }

        cellQueue.pop();//removes cell from front of queue 
    }


    std::vector<int> cellPath;//final path
    if (goalReached)// if destination cell was found
    {
        int currentCell = t_destCellId;//set current cell to destination cell id so we can back track the path

        while (currentCell != t_startCellId)//loops until start position is found
        {
            cellPath.push_back(currentCell);//adds cell to the path
            currentCell = previousCell[currentCell];//updates current cell to the previous cell 
        }
        cellPath.push_back(t_startCellId);//adds player starting cell to the path
        
    }

    return cellPath;//returns final path

}

int Grid::coordinateToGrid(sf::Vector2f coordinate)
{
    int col = (coordinate.x / m_cellWidth);
    int row = (coordinate.y / m_cellHeight);
    return (row * m_gridCols + col);
}