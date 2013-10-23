#include "Door.h"

Door::Door()
	: GameObject() {}

Door::Door(sf::Vector2f pos, sf::IntRect openS, sf::IntRect closedS, DoorState doorS, DoorDirection doorD)
	:GameObject(pos)
{
	position = pos;

	if (doorDirection == DOWN || doorDirection == UP)
		body = Body(position, sf::Vector2f(0, 0), sf::Vector2f(0, 0), Body::DOOR, 100, 50, 2);
    else
		body = Body(position, sf::Vector2f(0, 0), sf::Vector2f(0, 0), Body::DOOR, 50, 100, 2);

	openSource = openS;
	closedSource = closedS;
	currentSource = closedSource;
	doorState = doorS;
	doorDirection = doorD;
}

void Door::LoadContent(sf::Texture &texture)
{
	doorSprite.setTexture(texture);
	doorSprite.setTextureRect(currentSource);

	if (doorDirection == UP || doorDirection == DOWN)
		doorSprite.setOrigin(sf::Vector2f((float)Constants::tileSize, (float)Constants::tileSize/2));
	else
		doorSprite.setOrigin(sf::Vector2f((float)Constants::tileSize/2, (float)Constants::tileSize));

	doorSprite.setPosition(position);
}

void Door::Draw(sf::RenderWindow &window)
{	
	doorSprite.setTextureRect(currentSource);
	window.draw(doorSprite);
}