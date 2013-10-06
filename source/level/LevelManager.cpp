#include "LevelManager.h"

LevelManager &LevelManager::getInstance()
{
    static LevelManager instance;
    return instance;
}

LevelManager::LevelManager()
{    
}

LevelManager::~LevelManager()
{
}

void LevelManager::Initialize()
{
	//create the hub
    levelHub = Level(Level::Hub, levelDifficulty);
    levelHub.Initialize();
	
	//start level has difficulty 0, difficulty increases by 1 after a level is completed
	levelDifficulty = 0;

    //initialize the starting level and set it as the current level type
    currentLevelType = Level::Start;
    currentLevel = Level(currentLevelType, levelDifficulty);    
    currentLevel.Initialize();
	Room (*lvlRoomPtr)[10] = currentLevel.levelRooms;

	//generate the map for the current level
	generator = LevelGenerator(currentLevel.levelType, currentLevel.levelDifficulty, lvlRoomPtr);
	generator.generateMap();
	currentLevel.currentRoom = &currentLevel.levelRooms[generator.startPos.y][generator.startPos.x];
	
}

void LevelManager::LoadContent()
{
	currentLevel.LoadContent();
	//levelHub.LoadContent();
}

void LevelManager::Update(sf::Time elapsedTime)
{
    //update the current level
    currentLevel.Update();
}



void LevelManager::Draw(sf::RenderWindow &window)
{
    //draw the current level
    currentLevel.Draw(window);

	
}


void LevelManager::createNewLevel(Level::LevelType levelType)
{
    currentLevelType = levelType;
    Level level(currentLevelType, levelDifficulty);
    level.Initialize();
}