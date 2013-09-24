#include "LevelManager.h"

LevelManager::LevelManager()
{
    levelDifficulty = 0;

    //initialize the starting level and set it as the current level type
    currentLevelType = Level::start;
    currentLevel = Level(currentLevelType, levelDifficulty);

    //create the hub
    levelHub = Level(Level::hub, levelDifficulty);
    levelHub.initialize();
    currentLevel.initialize();
}


void LevelManager::onTick()
{
    //update the current level
    currentLevel.onTick();
}


void LevelManager::onEvent(const int eventType, const int param1, const int param2)
{
}


void LevelManager::onRender()
{


    //draw the current level
    currentLevel.onRender();

    m_video->clear(sf::Color::Blue);
}


void LevelManager::createNewLevel(Level::LevelType levelType)
{
    currentLevelType = levelType;
    Level level(currentLevelType, levelDifficulty);
    level.initialize();
}
