#pragma once
#include <SFML/Graphics.hpp>

class Cell
{
public:
	Cell(int t_cellId);



private:
	void initCell();
	void setNeighbours();
	int m_cellID;
	std::vector<int> m_neighbours;
	int m_rows = 10;
	int m_cols = 10;
};