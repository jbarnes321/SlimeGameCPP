#ifndef SLIMECONTROLLER_H_INCLUDED
#define SLIMECONTROLLER_H_INCLUDED

#include "../Engine/Includes.h"
#include "level/LevelManager.h"
#include <SFML/Audio.hpp>

class SlimeGame : public GameBase
{
    public:
		EventManager1<void, int> m_eventHandler;
		SlimeGame();
		~SlimeGame() {};

		LevelManager levelManager;

	private:
		void onTick();
		void onRender();
		void onEvent(const int eventType, const int param1, const int param2);
		void reset();

		sf::Vector2i m_screenSize;
};

typedef std::shared_ptr<SlimeGame> SlimePtr;

#endif // SLIMECONTROLLER_H_INCLUDED
