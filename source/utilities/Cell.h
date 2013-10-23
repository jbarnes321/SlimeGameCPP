#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "../Constants.h"

class Cell
{
	public:
		
		Cell();
		Cell(char tileID, int row, int col, Cell (*cellMapPtr)[12]);
		~Cell() {};
		
		void Initialize();
		
		char tileID;
		int row;
		int col;
		bool walkable;
		Cell *parent;
		sf::Vector2f gridCoord;
		Cell *north, *east, *south, *west, *northEast, *southEast, *southWest, *northWest;
		Cell (*cellMapPtr)[12];
		
	private:
	
		int G;
		int F;
		int H;		
};


#endif //CELL_H_INCLUDED