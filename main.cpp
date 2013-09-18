#include "Game/SlimeController.h"

int main()
{
/*
    //Player player = Player(sf::Vector2f(500, 300));
    //player.Initialize();

    //window.setFramerateLimit(60);



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
*/
    SlimePtr game(new SlimeGame());

    game->start();

    return 0;
}

