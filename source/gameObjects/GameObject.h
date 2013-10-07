#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include <string>
#include <SFML/Graphics.hpp>
#include "../Constants.h"

class GameObject
{
	public:
		GameObject(sf::Vector2f position);
		~GameObject();
	
		virtual void LoadContent();
		virtual void Update();
		virtual void Draw(sf::RenderWindow &window);
		void DrawShadow(sf::RenderWindow &window);

	private:
		std::string assetDir;

		int flashTime;

		sf::Vector2f position;

		sf::Color color;

		sf::Texture shadowTexture;
		sf::Sprite shadow;
		

};


#endif // GAMEOBJECT_H_INCLUDED