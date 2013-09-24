#ifndef LEVELGENERATOR_H_INCLUDED
#define LEVELGENERATOR_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include "Level.h"

class LevelGenerator
{
    public:

        LevelGenerator(Level &level, int difficulty);
        ~LevelGenerator() {};

        bool generateMap();

        std::vector<Room> specialRooms;

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

        int totalRoomCount;         // the total number of room layouts in maps.txt
        std::string mapFileDir;     //path directory to map.txt
        std::string specialRoomDir;//path to special room text files

        Level *level;               //pointer to the current level being built
        int levelDifficulty;

        Room *startRoom;

        sf::Vector2i position;


};

#endif // LEVELGENERATOR_H_INCLUDED
