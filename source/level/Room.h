#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "../Constants.h"

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
        Room(int row, int col, RoomType type, std::string mapName, int roomID, std::string levelType);
        ~Room() {};

		void LoadContent();
        void Update();
        void Draw(sf::RenderWindow &window);


        RoomType roomType;
        int roomID;
		sf::Vector2i levelPosition;

    private:
		void drawBorders(sf::RenderWindow &window);

		sf::Texture ec600Texture, ec800Texture;
		sf::Sprite edgeClosed600Right, edgeClosed600Left, edgeClosed800Top, edgeClosed800Bottom;
		sf::Texture tileSheetTexture;

		std::string levelDir;
		std::string mapName;

		struct Tile
		{
			int tileID;
			sf::Vector2f position;
			sf::IntRect tileImage;
			float scale;
		};

		std::vector<Tile> floorTiles;

};

#endif // ROOM_H_INCLUDED