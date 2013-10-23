#include "Animation.h"

Animation::Animation(sf::Texture sfTexture, sf::Time time, bool looping, int r, int c, int cRow)
{
	texture = sfTexture;
	frameTime = time;
	isLooping = looping;
	rows = r;
	cols = c;
	currentRow = cRow;
}


int Animation::getFrameWidth()
{
	return texture.getSize().x/cols;
}

int Animation::getFrameHeight()
{
	return texture.getSize().y/rows;
}

int Animation::getFrameCount()
{
	return texture.getSize().x/getFrameWidth();
}