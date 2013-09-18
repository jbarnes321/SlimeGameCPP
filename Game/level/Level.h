#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

class Level
{
    public:

        Level();
        ~Level() {};

        void initialize();
        void onTick();
        void onRender();
        void drawMiniMap();
        void getMiniMapSprite();
        void getAdjacentMiniMapRooms();

    private:

};


#endif // LEVEL_H_INCLUDED
