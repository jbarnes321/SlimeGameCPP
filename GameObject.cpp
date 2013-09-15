#include "GameObject.h"



GameObject::GameObject(sf::Vector2f pos)
{
    position = position;
    body = Body(pos, sf::Vector2f(0, 0), sf::Vector2f(0, 0), Body::wall, 50, 50, 1);
}

void GameObject::InitializeSprite()
{
    texture.loadFromFile(assetName);
    sprite.setTexture(texture);
    sprite.setPosition(position);

}
