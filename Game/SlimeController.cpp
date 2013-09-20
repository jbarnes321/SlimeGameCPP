#include "SlimeController.h"
#include <stdlib.h>

SlimeGame::SlimeGame()
{
    m_screenSize = sf::Vector2i(1000, 600);
    m_video->changeTitle("Revenge of the Slime");

    LevelManager();
}


void SlimeGame::onTick()
{

}

void SlimeGame::onRender()
{
    m_video->clear(sf::Color::Black);

    m_video->swapBuffers();
}

void SlimeGame::onEvent(const int eventType, const int param1, const int param2)
{
    m_eventHandler.trigger(eventType);

	switch (eventType)
	{
		case EVENT_KEYDOWN:
			switch (param1)
			{
				case KeyId::Escape://hits the ESC key, close the window
					stop();
					break;

				case KeyId::F1:
					reset();
					break;
			}
			break;

		case EVENT_QUIT://clicks the X button, close the window
			stop();

			break;
	}
}


void SlimeGame::reset()
{

}
