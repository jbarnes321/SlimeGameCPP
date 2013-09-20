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


void LevelManager::onRender()
{
    //draw the current level
    currentLevel.onRender();

    //draw the minimap, unless the current level is the hub
    if (currentLevelType != Level::hub)
        currentLevel.drawMiniMap();
}


void LevelManager::createNewLevel(Level::LevelType levelType)
{
    currentLevelType = levelType;
    Level level(currentLevelType, levelDifficulty);
    level.initialize();
}
