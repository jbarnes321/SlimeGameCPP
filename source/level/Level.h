#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED


#include <SFML/Graphics.hpp>

#include "Room.h"

class Level
{
    public:

        enum LevelType
        {
            Hub = 0,
            Start,
            Fire,
            Ice,
            Poison,
            Ghost,
            Electric,
            Earth,
            Necro,
            NONE
        } levelType;


        Level();
        Level(LevelType lType, int difficulty);
        ~Level() {};

        void Initialize();
		void LoadContent();
        void Update();
        void Draw(sf::RenderWindow &window);

        void drawMiniMap(sf::RenderWindow &window);
		sf::IntRect getMiniMapSprite(Room::RoomType type, bool flag);
        void adjacentMiniMapRooms(sf::Vector2i roomPosition);

		static std::string LevelTypeToString(Level::LevelType type);

        Room levelRooms[8][10];
        Room *currentRoom;

        int levelDifficulty;


    private:

		//the background image of the minimap
		sf::Texture mmbTexture;
		sf::Sprite miniMapBackgroundSprite;

		//the individual room images that are places on the minimap
		sf::Texture mmrTexture;        
		sf::Sprite miniMapRoomSprite;

		std::vector<Room*> oldRooms;
		std::vector<Room*> newRooms;

		bool drawEntireMap;

};


#endif // LEVEL_H_INCLUDED