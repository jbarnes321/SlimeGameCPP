#include <SFML/Graphics.hpp>
#include "Player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Revenge of the Slime");


    Player player = Player(sf::Vector2f(55, 10));
    player.Initialize();

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(player.sprite);
        window.display();
    }

    return 0;
}

