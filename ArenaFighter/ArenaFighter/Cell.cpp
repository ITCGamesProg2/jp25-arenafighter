#include "Cell.h"
#include <iostream>
Cell::Cell(int t_cellID)
	: m_cellID(t_cellID)
{
	initCell();
}


void Cell::initCell()
{
	std::cout << "\ncell created ID:"<<m_cellID;
	void setNeighbours();
}

void Cell::setNeighbours()
{

}