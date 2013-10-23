#ifndef DOOR_H_INCLUDED
#define DOOR_H_INCLUDED

#include "GameObject.h"
#include "../Constants.h"

class Door : public GameObject
{
	public:

		enum DoorState
        {
            OPEN = 0,
            LOCKEDOPEN,
            PORTALOPEN,
            CLOSED,
            LOCKEDCLOSED,
            PORTALCLOSED,
        } doorState;

        enum DoorDirection
        {
            UP = 0,
            DOWN,
            LEFT,
            RIGHT
        } doorDirection;

		Door();
		Door(sf::Vector2f pos, sf::IntRect openSource, sf::IntRect closedSource, DoorState doorState, DoorDirection doorDirection);
		~Door() {};
		

		void LoadContent(sf::Texture &texture);
		void Draw(sf::RenderWindow &window);

		sf::IntRect openSource;
		sf::IntRect closedSource;
		sf::IntRect currentSource;
		

	private:

		sf::Texture doorTexture;
		sf::Sprite doorSprite;
		

};

#endif //DOOR_H_INCLUDED