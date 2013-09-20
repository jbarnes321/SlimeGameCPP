#ifndef LEVELMANAGER_H_INCLUDED
#define LEVELMANAGER_H_INCLUDED

#include "Level.h"

class LevelManager
{
    public:

        LevelManager();
        ~LevelManager() {};


        void onTick();
        void onRender();
        void createNewLevel(Level::LevelType levelType);

        Level currentLevel;
        Level levelHub;

        Level::LevelType currentLevelType;

        int levelDifficulty;

    private:

};


#endif // LEVELMANAGER_H_INCLUDED
