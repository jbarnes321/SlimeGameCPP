#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "../Constants.h"
#include "../gameObjects/Wall.h"
#include "../gameObjects/Door.h"
#include "../gameObjects/enemies/Enemy.h"
#include "../utilities/Cell.h"

class Room
{
    public:

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
            LASTROOM,
			NONE
        };

        Room();
        Room(int row, int col, RoomType type, std::string mapName, int roomID, std::string levelType, Room (*levelRoomPtr)[10]);
        ~Room() {};

		void LoadContent();
        void Update();
        void Draw(sf::RenderWindow &window);

		void createDoors(std::string &levelType, sf::Texture *doorTextures);


        RoomType roomType;
        int roomID;
		sf::Vector2i levelPosition;
		
		int row, col;
		
		std::vector<Wall> wallsInRoom;
		std::vector<Door> doorsInRoom;
		std::vector<Enemy> enemiesInRoom;

    private:
		void drawBorders(sf::RenderWindow &window);
		Door::DoorState getDoorState(Door::DoorDirection direction);
		bool checkDoorDirection(Door::DoorDirection doorDirection);
		void unlockDoors();

		sf::Texture ec600Texture, ec800Texture;
		sf::Sprite edgeClosed600Right, edgeClosed600Left, edgeClosed800Top, edgeClosed800Bottom;
		sf::Texture tileSheetTexture;

		std::string levelDir;
		std::string mapName;


		Room (*lvlRoomPtr)[10];

		//Cell cellMap[16][12];

		struct Tile
		{
			int tileID;
			sf::Vector2f position;
			sf::IntRect tileImage;
			float scale;
		};

		std::vector<Tile> floorTiles;

		bool unlocked;

};

#endif // ROOM_H_INCLUDED