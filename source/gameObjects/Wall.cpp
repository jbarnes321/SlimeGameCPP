#include "Wall.h"

Wall::Wall()
	: GameObject() {}

Wall::Wall(sf::Vector2f pos, std::string assetName, bool isDestByPlayer, bool isDestByEnemy, sf::IntRect sourceRec)
	:GameObject(pos)
{
	position = pos;
	body = Body(position, sf::Vector2f(0, 0), sf::Vector2f(0, 0), Body::WALL, 50, 50, 2);
	assetDir = assetName;
	isDestroyableByPlayer = isDestByPlayer;
	isDestroyableByEnemy = isDestByEnemy;
	sourceRect = sourceRec;
	killed = false;

}

void Wall::LoadContent()
{
}

void Wall::LoadContent(sf::Texture &texture)
{
	wallSprite.setTexture(texture);
	wallSprite.setTextureRect(sourceRect);
	wallSprite.setOrigin(25, 25);
}

void Wall::Draw(sf::RenderWindow &window)
{
	wallSprite.setPosition(position);
	window.draw(wallSprite);
}