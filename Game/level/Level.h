#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Room.h"


class Level
{
    public:

        enum LevelType
        {
            hub = 0,
            start,
            fire,
            ice,
            poison,
            ghost,
            electric,
            earth,
            necro,
            NONE
        } levelType;


        Level();
        Level(LevelType lType, int difficulty);
        ~Level() {};

        void initialize();
        void onTick();
        void onRender();
        void drawMiniMap();
        void getMiniMapSprite();
        void getAdjacentMiniMapRooms();

        Room levelRooms[8][10];
        Room *currentRoom;

        int levelDifficulty;



    private:

};


#endif // LEVEL_H_INCLUDED
