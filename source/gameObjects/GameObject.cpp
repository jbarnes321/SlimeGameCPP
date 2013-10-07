#include "GameObject.h"

GameObject::GameObject(sf::Vector2f pos)
{
	position = pos;
	flashTime = 0;
	color = sf::Color::White;
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