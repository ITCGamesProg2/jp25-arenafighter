#include "SpatialPartitionGrid.h"

std::pair<int, int> SpatialPartitionGrid::getCellCoordinates(const sf::Vector2f& t_position)
{
	return std::pair<int, int>(
		//floor rounds down to the nearest int
		floor(t_position.x / m_cellWidth),
		floor(t_position.y / m_cellHeight)
	);
}

void SpatialPartitionGrid::insertGameObjectIntoGrid(sf::FloatRect* t_boundingBox)
{
	// Convert the position of the top left and bottom right of the game object to a pair of ints representing row and col of grid it resides in
	std::pair<int, int> topLeft = getCellCoordinates(sf::Vector2f(t_boundingBox->left, t_boundingBox->top));
	std::pair<int, int> bottomRight = getCellCoordinates(sf::Vector2f(t_boundingBox->left + t_boundingBox->width, t_boundingBox->top + t_boundingBox->height));

	// This loop will iterate through all rows and columns of the grid and populate them with the bounding box passed to the function
	// Objects that are on a grip cell overlap will be inserted into all cells it touches
	for (int x = topLeft.first; x <= bottomRight.first; x++)
	{
		for (int y = topLeft.second; y <= bottomRight.second; y++)
		{
			grid[std::pair<int, int>(x, y)].push_back(t_boundingBox);
		}
	}
}

std::vector<sf::FloatRect> SpatialPartitionGrid::getNearbyObjects(const sf::FloatRect* t_boundingBox)
{
	std::vector<sf::FloatRect> nearbyObjects;

	// Convert the position of the top left and bottom right of the game object to a pair of ints representing row and col of grid it resides in
	std::pair<int, int> topLeft = getCellCoordinates(sf::Vector2f(t_boundingBox->left, t_boundingBox->top));
	std::pair<int, int> bottomRight = getCellCoordinates(sf::Vector2f(t_boundingBox->left + t_boundingBox->width, t_boundingBox->top + t_boundingBox->height));

	// This loop will check the 3x3 area around the object the function was called on
	for (int x = topLeft.first - 1; x <= bottomRight.first + 1; x++)
	{
		for (int y = topLeft.second - 1; y <= bottomRight.second; y++)
		{
			// This if statement is making sure the object exists within a cell in the grid
			if (grid.count({ x, y }))
			{
				for (const auto& rectangle : grid.at({ x,y }))
				{
					// This is ensuring we dont add the object passed to the function isnt included in vector of nearby objects
					if (!(rectangle->left == t_boundingBox->left && rectangle->top == t_boundingBox->top &&
						rectangle->width == t_boundingBox->width && rectangle->height == t_boundingBox->height))
					{
						nearbyObjects.push_back(*rectangle);
					}
				}
			}
		}
	}
	return nearbyObjects;
}


void SpatialPartitionGrid::drawGrid(sf::RenderWindow& t_window,const sf::FloatRect* t_playerBounds, bool t_debugMode)
{
	sf::RectangleShape cell;
	cell.setSize(sf::Vector2f(m_cellWidth, m_cellHeight));
	cell.setFillColor(sf::Color(0, 0, 255, 128));
	cell.setOutlineColor(sf::Color(100, 100, 100, 128));
	cell.setOutlineThickness(1.0f);

	// Calculate the number of cells that will fit within the window
	int noOfCellsX = t_window.getSize().x / m_cellWidth; 
	int noOfCellsY = t_window.getSize().y / m_cellHeight;

	if (t_debugMode)
	{
		for (int x = 0; x < noOfCellsX; x++)
		{
			for (int y = 0; y < noOfCellsY; y++)
			{
				sf::FloatRect cellBounds(x * m_cellWidth, y * m_cellHeight, m_cellWidth, m_cellHeight);

				if (t_playerBounds && cellBounds.intersects(*t_playerBounds))
				{
					cell.setFillColor(sf::Color(255, 0, 0, 128));
				}
				else
				{
					cell.setFillColor(sf::Color(0, 0, 255, 128));
				}
				cell.setPosition(x * m_cellWidth, y * m_cellHeight);
				t_window.draw(cell);
			}
		}
	}

}



// When using moving objects like the player, the grid will need to be cleared and repopulated to reflect position changes
void SpatialPartitionGrid::clearGrid()
{
	grid.clear();
}
