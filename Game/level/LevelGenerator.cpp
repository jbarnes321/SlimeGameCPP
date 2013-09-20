#include "LevelGenerator.h"

LevelGenerator::LevelGenerator(Level &lvl, int difficulty)
{
    totalRoomCount = 10;
    level = &lvl;
    levelDifficulty = difficulty;
}


void LevelGenerator::pickStartRoom()
{
    // Center of the level map.
    int col = 5;    // x coordinate
    int row = 4;    // y coordinate

    // Selects some random offset from the center of the level map.
    col += Constants::random(col + 2, col - 2);
    row += Constants::random(row + 2, row - 2);

    // Creates the HUB level.
    if(level->levelType == Level::hub)
        level->levelRooms[row][col] = Room();

    // Creats the initial room, which is empty.
    else
        level->levelRooms[row][col] = Room();

    startRoom = level->rooms[row][col];
    position = new Vector2(col, row);
}

 // This function returns the number of rooms each floorType should have.
int LevelGenerator::budget()
{
    int value;
    // Switches between levelTypes and returns the roomBudget.

    if (level->levelType == Level::hub)
        return 1;

    switch (levelDifficulty)
    {
        case 0:
            value = 7;
            break;
        case 1:
            value = 9;
            break;
        case 2:
            value = 12;
            break;
        case 3:
            value = 15;
            break;
        case 4:
            value = 18;
            break;
        case 5:
            value = 21;
            break;
        case 6:
            value = 23;
            break;
        case 7:
            value = 25;
            break;
        case 8:
            value = 27;
            break;
        case 9:
            value = 30;
            break;
        default:
            value = 9;
            break;
    }

    return value;

}
