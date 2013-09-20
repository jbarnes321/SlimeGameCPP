#include "Level.h"

Level::Level() {}

Level::Level(LevelType lType, int difficulty)
{
    levelType = lType;
    levelDifficulty = difficulty;
}


void Level::initialize()
{


}


void Level::onTick()
{
    currentRoom->onTick();
}


void Level::onRender()
{
    currentRoom->onRender();
}


void Level::drawMiniMap()
{

}


void Level::getMiniMapSprite()
{

}


void Level::getAdjacentMiniMapRooms()
{

}
