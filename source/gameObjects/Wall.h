#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#include "GameObject.h"

class Wall : public GameObject
{
	public:

		Wall();
		Wall(sf::Vector2f pos, std::string assetName, bool isDestroyableByPlayer, bool isDestroyableByEnemy, sf::IntRect sourceRect);
		~Wall() {};
		

		void LoadContent();
		void LoadContent(sf::Texture &texture);
		void Draw(sf::RenderWindow &window);

	private:

		sf::Sprite wallSprite;
		sf::IntRect sourceRect;

		bool isDestroyableByPlayer;
		bool isDestroyableByEnemy;
		bool killed;

};

#endif //WALL_H_INCLUDED