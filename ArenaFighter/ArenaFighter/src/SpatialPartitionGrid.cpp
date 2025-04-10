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

	m_cellsChecked = 0;
	m_collisionPairs = 0;
	//m_collisionClock.restart();

	std::vector<sf::FloatRect> nearbyObjects;

	// Convert the position of the top left and bottom right of the game object to a pair of ints representing row and col of grid it resides in
	std::pair<int, int> topLeft = getCellCoordinates(sf::Vector2f(t_boundingBox->left, t_boundingBox->top));
	std::pair<int, int> bottomRight = getCellCoordinates(sf::Vector2f(t_boundingBox->left + t_boundingBox->width, t_boundingBox->top + t_boundingBox->height));

	// This loop will check the 3x3 area around the object the function was called on
	for (int x = topLeft.first - 1; x <= bottomRight.first + 1; x++)
	{
		for (int y = topLeft.second - 1; y <= bottomRight.second; y++)
		{
			m_cellsChecked++;
			// This if statement is making sure the object exists within a cell in the grid
			if (grid.count({ x, y }))
			{
				for (const auto& rectangle : grid.at({ x,y }))
				{
					m_collisionPairs++;
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
	//m_collisionTime = m_collisionClock.getElapsedTime().asMilliseconds();

	m_maxCellsChecked = std::max(m_maxCellsChecked, m_cellsChecked);
	m_maxCollisionPairs = std::max(m_maxCollisionPairs, m_collisionPairs);
	//m_maxCollisionTime = std::max(m_maxCollisionTime, m_collisionTime);

	return nearbyObjects;
}


void SpatialPartitionGrid::drawGrid(sf::RenderWindow& t_window,const sf::FloatRect* t_playerBounds, bool t_debugMode)
{
	m_debugStringStream.str("");
	m_debugStringStream.clear();

	m_debugStringStream << "Current:\n"
		<< "Cells Checked: " << m_cellsChecked << "\n"
		<< "Collision Pairs: " << m_collisionPairs << "\n"
		<< "Time taken to check: " << m_collisionTime << " microseconds!\n"
		<< "Maximums: \n"
		<< "Max Cells Checked: " << m_maxCellsChecked << "\n"
		<< "Maxumum Pairs Checked: " << m_maxCollisionPairs << "\n"
		<< "Max Time: " << m_maxCollisionTime << " microseconds\n";

	m_debugInfoText.setString(m_debugStringStream.str());
	

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
		t_window.draw(m_debugInfoText);
	}

}



// When using moving objects like the player, the grid will need to be cleared and repopulated to reflect position changes
void SpatialPartitionGrid::clearGrid()
{
	grid.clear();
}

void SpatialPartitionGrid::initFontForDebug()
{
	if (!m_font.loadFromFile("ASSETS/FONTS/PixelPurl.ttf"))
	{
		std::cout << "Error loading font for debug info pane!\n";
	}

	m_debugInfoText.setFont(m_font);
	m_debugInfoText.setFillColor(sf::Color::White);
	m_debugInfoText.setCharacterSize(20);
	m_debugInfoText.setPosition(1150.0f, 10.0f);
}
