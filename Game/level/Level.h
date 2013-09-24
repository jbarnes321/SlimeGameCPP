#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "Room.h"

class Level : public GameBase
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
        void onEvent(const int eventType, const int param1, const int param2);
        void onRender();
        void drawMiniMap();
        void getMiniMapSprite();
        void getAdjacentMiniMapRooms();

        Room levelRooms[8][10];
        Room *currentRoom;

        int levelDifficulty;


    private:

        sf::Texture miniMapBackgroundTexture;
        sf::Sprite miniMapBackgroundSprite;

};


#endif // LEVEL_H_INCLUDED
