#include "LevelManager.h"

LevelManager &LevelManager::getInstance()
{
    static LevelManager instance;
    return instance;
}

LevelManager::LevelManager() :
	scene(&Scene(sf::Vector2f(0, 0)))
{    
}

LevelManager::~LevelManager()
{
}

void LevelManager::Initialize(sf::Clock sfClock, Scene *roomScene)
{
	clock = sfClock;
	scene = roomScene;

	player = Player(sf::Vector2f(400, 350), clock);

	scene->addBodyCurrent(&player.body);


	//create the hub
    levelHub = Level(Level::Hub, levelDifficulty, roomScene);
    levelHub.Initialize();
	
	//start level has difficulty 0, difficulty increases by 1 after a level is completed
	levelDifficulty = 0;

    //initialize the starting level and set it as the current level type
    currentLevelType = Level::Start;
	currentLevel = Level(currentLevelType, levelDifficulty, scene);    
    currentLevel.Initialize();
	Room (*lvlRoomPtr)[10] = currentLevel.levelRooms;

	//generate the map for the current level
	generator = LevelGenerator(currentLevel.levelType, currentLevel.levelDifficulty, lvlRoomPtr);
	generator.generateMap();
	currentLevel.currentRoom = &currentLevel.levelRooms[generator.startPos.y][generator.startPos.x];
	
}

void LevelManager::LoadContent()
{
	player.LoadContent();
	currentLevel.LoadContent();
	//levelHub.LoadContent();
}

void LevelManager::Update(sf::Time elapsedTime, sf::Event event)
{
	//update the player
	player.Update(event);

	//add player's body to the vector if it is not already in the vector
	if (!(std::find(scene->currentRoomBodies.begin(), scene->currentRoomBodies.end(), &player.body) != scene->currentRoomBodies.end()))
	{
		scene->currentRoomBodies.push_back(&player.body);
	}

    //update the current level
    currentLevel.Update(player);
	
}



void LevelManager::Draw(sf::RenderWindow &window)
{
    //draw the current level
    currentLevel.Draw(window);
	player.Draw(window);

	
}


void LevelManager::createNewLevel(Level::LevelType levelType)
{
    currentLevelType = levelType;
    Level level(currentLevelType, levelDifficulty, scene);
    level.Initialize();
}