#pragma once
#include <SFML/Graphics.hpp>

class Cell
{
public:
	Cell(int t_cellId,int t_gridRows, int t_gridCols);

	std::vector<int>& getNeighbours();
	bool isMarked() const; // returns the member variable m_marked;
	void setMarked(bool t_val); // setter method to set the value of member m_marked
private:
	void initCell();
	void setNeighbours();
	int m_cellID;
	int m_gridRows;
	int m_gridCols;
	std::vector<int> m_neighbours;
	bool m_marked{ false };
};