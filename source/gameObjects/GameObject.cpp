#include "GameObject.h"

GameObject::GameObject() {};

GameObject::GameObject(sf::Vector2f pos)
{
	position = pos;
	flashTime = 0;
	color = sf::Color::White;
}

GameObject::GameObject(sf::Vector2f pos, sf::Clock sfClock)
{
	position = pos;
	clock = sfClock;
	flashTime = 0;
	color = sf::Color::White;
	body = Body(position, sf::Vector2f(0, 0), sf::Vector2f(0, 0), Body::PLAYER, 50, 50, 1);
}

void GameObject::LoadContent()
{
	if(!shadowTexture.loadFromFile("assets/noShadow.png"))
	{
		return;
	}

	shadow.setTexture(shadowTexture);
}

void GameObject::Update()
{
}

void GameObject::Draw(sf::RenderWindow &window)
{
}

void GameObject::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(position);
	window.draw(shadow);
}