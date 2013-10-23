#ifndef LEVELMANAGER_H_INCLUDED
#define LEVELMANAGER_H_INCLUDED

/*
*	A singleton class that manages the creation and player progression between levels.
*/

#include "Level.h"
#include "LevelGenerator.h"
#include "../gameObjects/Player.h"


class LevelManager
{
    public:        
        ~LevelManager();
		static LevelManager &getInstance();

		void Initialize(sf::Clock sfClock, Scene *scene);
		void LoadContent();
        void Update(sf::Time elapsedTime, sf::Event event);
        void Draw(sf::RenderWindow &window);

        void createNewLevel(Level::LevelType levelType);

		sf::Clock clock;
		Player player;
        
    private:
		LevelManager();
		LevelManager(LevelManager const&);
		void operator=(LevelManager const&);
	
		Level currentLevel;		//the current level that the player is in
        Level levelHub;		//the level that the palyer returns to after completing other levels

		LevelGenerator generator;

        Level::LevelType currentLevelType;

        int levelDifficulty;

		Scene *scene;
};


#endif // LEVELMANAGER_H_INCLUDED