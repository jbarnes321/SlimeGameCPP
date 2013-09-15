#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "GameObject.h"

class Player : public GameObject
{

    public:

        //constructor
        Player(sf::Vector2f position);

        void Initialize();

};

#endif // PLAYER_H_INCLUDED
