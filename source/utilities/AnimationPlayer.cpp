#include "AnimationPlayer.h"

void AnimationPlayer::PlayAnimation(Animation nextAnimation)
{
	// If this animation is already running, do not restart it.
	if (&animation == &nextAnimation)
		return;

	// Start the new animation.
	animation = nextAnimation;
	frameIndex = 0;
	time = sf::seconds(0);
}

void AnimationPlayer::Draw(sf::RenderWindow &window, sf::Vector2f position, sf::Vector2f origin, sf::Clock clock)
{	
		
	//Process the passing time
	time += clock.getElapsedTime();
	while (time.asSeconds() > animation.frameTime.asSeconds())
	{
		time -= sf::Time(animation.frameTime);

		//Advance the frame index, looping or clamping as appropriate
		if (animation.isLooping)
		{
			frameIndex = (frameIndex + 1) % animation.getFrameCount();
		}
		else
		{
			frameIndex = std::min(frameIndex + 1, animation.getFrameCount() - 1);
		}
	}
	
	int width = animation.getFrameWidth();
	int height = animation.getFrameHeight();
	int column = frameIndex % animation.cols;
	
	sf::IntRect source = sf::IntRect(width * column, height * animation.currentRow, width, height);
	
	sf::Sprite sprite;
	sprite.setTexture(animation.texture);
	sprite.setTextureRect(source);
	sprite.setPosition(position);
	sprite.setOrigin(origin);
	
	window.draw(sprite);
}