#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include <string>
#include <SFML/Graphics.hpp>
#include "../Constants.h"
#include "../utilities/AnimationPlayer.h"
#include "../utilities/physics/Body.h"

class GameObject
{
	public:
		GameObject();
		GameObject(sf::Vector2f pos);
		GameObject(sf::Vector2f position, sf::Clock clock);
		~GameObject() {};
	
		virtual void LoadContent();
		virtual void Update();
		virtual void Draw(sf::RenderWindow &window);
		void DrawShadow(sf::RenderWindow &window);

		Body body;
		sf::Vector2f position;
		sf::Vector2f origin;

	protected:
		
		sf::Clock clock;		
		std::string assetDir;

	private:		

		int flashTime;	

		sf::Color color;

		sf::Texture shadowTexture;
		sf::Sprite shadow;
		

};


#endif // GAMEOBJECT_H_INCLUDED