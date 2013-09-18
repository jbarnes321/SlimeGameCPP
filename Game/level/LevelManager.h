#ifndef LEVELMANAGER_H_INCLUDED
#define LEVELMANAGER_H_INCLUDED

#include "Level.h"

class LevelManager
{
    public:

        LevelManager();
        ~LevelManager() {};

        enum LevelType
        {
            hub = 0,
            start,
            fire,
            ice,
            poison,
            ghost,
            electric,
            earth,
            necro,
            NONE
        };

        void onTick();
        void onRender();
        void createNewLevel(LevelType levelType);

        Level currentLevel;
        Level hubLevel;

        int levelDifficulty;

    private:

};


#endif // LEVELMANAGER_H_INCLUDED
