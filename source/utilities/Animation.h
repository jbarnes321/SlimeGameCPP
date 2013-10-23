#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <SFML/Graphics.hpp>

class Animation
{
	public:
	
		Animation() {};
		Animation(sf::Texture texture, sf::Time frameTime, bool isLooping, int rows, int cols, int currentRow);
		~Animation() {};
		
		int getFrameWidth();
		int getFrameHeight();
		int getFrameCount();
		
		sf::Texture texture;
		sf::Time frameTime;
		bool isLooping;
		int frameWidth;
		int frameHeight;
		
		int rows;
		int cols;
		int currentRow;
	
	private:
};

#endif //ANIMATION_H_INCLUDED