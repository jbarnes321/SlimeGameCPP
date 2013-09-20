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

        // Enum specifying the room type
        enum RoomType
        {
            HUB = 0,
            FIRST,
            NORMAL,
            MINIBOSS,
            BOSS,
            TREASURE,
            SHOP,
            LASTROOM
        };

        void generateMap();

    private:

        void pickStartRoom();
        int budget();
        void getSpecials();
        void addRoom(sf::Vector2i, RoomType roomType);
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


};

#endif // LEVELGENERATOR_H_INCLUDED
