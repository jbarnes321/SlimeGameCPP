#include "Room.h"

Room::Room()
{

}


Room::Room(int r, int c, RoomType type, std::string mName, int ID, std::string levelType)
{
    roomID = ID;
    roomType = type;
	levelPosition = sf::Vector2i(c, r);	//the position on the minimap, rows = y, col = x
	levelDir = "assets/level/" + levelType + "/";
}


void Room::LoadContent()
{
	if(!ec600Texture.loadFromFile(levelDir + "edgeClosed600.png"))
	{
		return;
	}
	if(!ec800Texture.loadFromFile(levelDir + "edgeClosed800.png"))
	{
		return;
	}

	edgeClosed600Left.setTexture(ec600Texture);
	edgeClosed600Right.setTexture(ec600Texture);
	edgeClosed800Bottom.setTexture(ec800Texture);
	edgeClosed800Top.setTexture(ec800Texture);
}


void Room::onTick()
{

}


void Room::onRender(sf::RenderWindow &window)
{
	for(std::vector<int>::size_type i = 0; i != floorTiles.size(); i++)
	{
		//sf::Texture
    /* std::cout << someVector[i]; ... */
	}

	drawBorders(window);
}


void Room::drawBorders(sf::RenderWindow &window)
{
	edgeClosed800Top.setPosition(0, 50);
	edgeClosed800Bottom.setPosition(800, 650);
	edgeClosed800Bottom.setRotation(180);
	edgeClosed600Left.setPosition(0, 50);
	edgeClosed600Right.setPosition(800, 650);
	edgeClosed600Right.setRotation(180);

	window.draw(edgeClosed800Top);
	window.draw(edgeClosed800Bottom);
	window.draw(edgeClosed600Left);
	window.draw(edgeClosed600Right);
}