#include "Cell.h"

Cell::Cell() :
north(&Cell()),
east(&Cell()),
south(&Cell()),
west(&Cell()),
northEast(&Cell()),
southEast(&Cell()),
southWest(&Cell()),
northWest(&Cell()),
parent(&Cell())
{
}

Cell::Cell(char ID, int r, int c, Cell (*cellMapP)[12]) :
north(&cellMapP[0][0]),
east(&cellMapP[0][0]),
south(&cellMapP[0][0]),
west(&cellMapP[0][0]),
northEast(&cellMapP[0][0]),
southEast(&cellMapP[0][0]),
southWest(&cellMapP[0][0]),
northWest(&cellMapP[0][0]),
parent(&cellMapP[0][0])
{
	tileID = ID;
	row = r;
	col = c;
	cellMapPtr = cellMapP;
}

void Cell::Initialize()
{
	 //if tileID = #, then it is a wall, not walkable
	if (tileID == '#' || tileID == '|')
	{
		walkable = false;
	}

	else
		walkable = true;

	F = 0;
	H = 0;
	G = 0;

	
	//the coordinate for the center of the tile
	//+50 because the first row is 50 units below the top of the screen
    gridCoord = sf::Vector2f(col * Constants::tileSize + Constants::tileSize / 2, 
							(row * Constants::tileSize + Constants::tileSize / 2) + 50);
							
	//pointers to all adjacent cells
	if (row - 1 >= 0)
		north = &cellMapPtr[row - 1][col];
	if (col - 1 >= 0)
		west = &cellMapPtr[row][col - 1];
	if (col + 1 <= 16 - 1)
		east = &cellMapPtr[row][col + 1];
	if (row + 1 <= 12 - 1)
		south = &cellMapPtr[row + 1][col];
	
	if ((row - 1 >= 0) && (col + 1 <= 16 - 1))
		northEast = &cellMapPtr[row - 1][col + 1];
	if ((row + 1 <= 12 - 1) && (col + 1 <= 16 - 1))
		southEast = &cellMapPtr[row + 1][col + 1];
	if ((row + 1 <= 12 - 1) && (col - 1 >= 0))
		southWest = &cellMapPtr[row + 1][col - 1];
	if ((row - 1 >= 0) && (col - 1 >= 0))
		northWest = &cellMapPtr[row - 1][col - 1];
		
}