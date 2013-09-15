#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include "Body.h"

class GameObject
{

    public:

        //constructor
        GameObject(sf::Vector2f position);

        void InitializeSprite();

        std::string assetName;
        sf::Vector2f position;

        sf::Texture texture;
        sf::Sprite sprite;

        Body body;

};
#endif // GAMEOBJECT_H_INCLUDED
