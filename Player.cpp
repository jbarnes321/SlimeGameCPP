#include "Player.h"

Player::Player(sf::Vector2f pos) :
    GameObject(pos)
{
    assetName = "assets/player/slimeSprite.png";
}

void Player::Initialize()
{
    GameObject::InitializeSprite();
}
