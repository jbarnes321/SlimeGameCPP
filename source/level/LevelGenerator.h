#ifndef LEVELGENERATOR_H_INCLUDED
#define LEVELGENERATOR_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>


#include "../Constants.h"
#include "Room.h"
#include "Level.h"


class LevelGenerator
{
    public:

		LevelGenerator();
        LevelGenerator(Level::LevelType type, int difficulty, Room (*lvlRPtr)[10]);
        ~LevelGenerator() {};

        bool generateMap();

		sf::Vector2i startPos;
		//Room startRoom;
		//Room *levelRooms[8][10];               //the current level being built
		int levelDifficulty;
		Level::LevelType levelType;

    private:

        void pickStartRoom();
        int budget();
        int getSpecials();
        void addRoom(sf::Vector2i, Room::RoomType roomType);
        int checkDirection(int direction, int prev, int length);
        sf::Vector2i getDifferenceVector(int direction);
        bool outOfBounds(sf::Vector2i);
        std::vector<sf::Vector2i> getLonelies();
        int getAdjacentRoomCount(sf::Vector2i position);
		std::string LevelTypeToString(Level::LevelType type);

        int totalRoomCount;         // the total number of room layouts in maps.txt
        std::string mapFileDir;     //path directory to map.txt
        std::string specialRoomDir;	//path to special room text files

		Room (*lvlRoomPtr)[10];
        
               

        sf::Vector2i position;


};

#endif // LEVELGENERATOR_H_INCLUDED