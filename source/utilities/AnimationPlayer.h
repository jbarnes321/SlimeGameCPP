#ifndef ANIMATIONPLAYER_H_INCLUDED
#define ANIMATIONPLAYER_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "Animation.h"

class AnimationPlayer
{
	public:
		Animation animation;	//the animation which is currently playing
		int frameIndex;			//the index of the current frame in the animation
		sf::Time time;			//the amount of time in seconds that the current frame has been shown for.
		
		void PlayAnimation(Animation animation);//begins or continues playback of an animation
		void Draw(sf::RenderWindow &window, sf::Vector2f position, sf::Vector2f origin, sf::Clock clock); //advances the time position and draws the current frame of the animation
		
	
	private:
	
};


#endif //ANIMATIONPLAYER_H_INCLUDED