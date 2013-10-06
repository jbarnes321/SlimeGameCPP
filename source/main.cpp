#include "level/LevelManager.h"
#define ScreenWidth 1000
#define ScreenHeight 650

int main()
{
    sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "Revenge of the Slime");

	sf::Clock clock;

	LevelManager::getInstance().Initialize();
	LevelManager::getInstance().LoadContent();


    // run the program as long as the window is open
    while (window.isOpen())
    {
		sf::Time dt = clock.restart();

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                // window closed
                case sf::Event::Closed:
                    window.close();
                    break;
			}        
			window.clear();

			LevelManager::getInstance().Update(dt);

			LevelManager::getInstance().Draw(window);			

			window.display();
		}
    }

    return 0;
}
