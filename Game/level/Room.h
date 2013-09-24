#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include "../../Constants.h"
#include "../../Engine/Includes.h"
#include <string>
#include <SFML/Graphics.hpp>

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
            LASTROOM
        };

        Room();
        Room(int row, int col, RoomType type, std::string mapName, int roomID);
        ~Room() {};

        void onTick();
        void onRender();


        RoomType roomType;
        int roomID;

    private:

};

#endif // ROOM_H_INCLUDED
