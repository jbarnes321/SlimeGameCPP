#include "Level.h"

Level::Level() {}

Level::Level(LevelType lType, int difficulty)
{
    levelType = lType;
    levelDifficulty = difficulty;


    bool errorLoading = false;

    if (!miniMapBackgroundTexture.loadFromFile("assets/minimap/mapBackground.png"))
	{
		errorLoading = true;
	}

	if(errorLoading)
	{
		stop();

		return;
	}


	miniMapBackgroundSprite.setTexture(miniMapBackgroundTexture);
	miniMapBackgroundSprite.setPosition(sf::Vector2f(100, 100));



}


void Level::initialize()
{
    //initialize every room in the level to NULL
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            levelRooms[j][i] = Room(i, j, Room::NORMAL, "NULL", -1);
        }
    }


}


void Level::onTick()
{
    currentRoom->onTick();
}


void Level::onEvent(const int eventType, const int param1, const int param2)
{
}


void Level::onRender()
{
     //draw the minimap, unless the current level is the hub
    if (levelType != hub)
        drawMiniMap();

    currentRoom->onRender();


}


void Level::drawMiniMap()
{
    m_video->draw(miniMapBackgroundSprite);
}


void Level::getMiniMapSprite()
{

}


void Level::getAdjacentMiniMapRooms()
{

}
