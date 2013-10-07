#include "Room.h"

Room::Room()
{

}


Room::Room(int r, int c, RoomType type, std::string mName, int ID, std::string levelType)
{
    roomID = ID;
    roomType = type;
	levelPosition = sf::Vector2i(c, r);	//the position on the minimap, rows = y, col = x
	mapName = mName;
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
	if(!tileSheetTexture.loadFromFile(levelDir + "tileFloorSpriteSheet.png"))
	{
		return;
	}

	edgeClosed600Left.setTexture(ec600Texture);
	edgeClosed600Right.setTexture(ec600Texture);
	edgeClosed800Bottom.setTexture(ec800Texture);
	edgeClosed800Top.setTexture(ec800Texture);

	std::ifstream infile(mapName);
	std::string nextLine;

	if (!infile.is_open())
	{
		return; //file not found
	}
	else
	{
		//skip 13 lines for each room in map.txt until to reach the needed room
		for (int i = 0; i < roomID * 13; i++)
		{
			std::getline(infile, nextLine);
		}



		for (int j = 0; j < 12; j++)
		{
			std::getline(infile, nextLine);

			for (int i = 0; i < 16; i++)
			{
				char tileID = nextLine[i];

				//create a new tile for each cell in the room
				Tile temp;

				//the position for each cell/tile. this is the center of the cell/tile
				sf::Vector2f tempVector((float)Constants::tileSize * i + 25, (float)Constants::tileSize * j + 75);				
				temp.position = tempVector;

				if (tileID == '#')//edge of the room wall
				{

				}
				else if (tileID == '|')//normal walls
				{
				}
				else if (tileID == '.')//empty tile
				{					
					temp.tileID = Constants::random(0, 3);
					temp.tileImage = sf::IntRect((temp.tileID % 4) * Constants::tileSize, 
												(temp.tileID / 4) * Constants::tileSize, Constants::tileSize, Constants::tileSize);					
					
				}
				else if (tileID == 's')//spike
				{
				}
				else if (tileID == 'v')//fire vent
				{
				}
				else if (tileID == 'p')//pickup
				{
				}
				else if (tileID == '@')//pickup drop position
				{
				}
				else if (tileID == 'c')//chest
				{
				}

				floorTiles.push_back(temp);

			}
		}

	}
	infile.close();
	
}


void Room::Update()
{

}


void Room::Draw(sf::RenderWindow &window)
{
	for(std::vector<int>::size_type i = 0; i != floorTiles.size(); i++)
	{
		sf::Sprite tileSprite;
		tileSprite.setTexture(tileSheetTexture);
		tileSprite.setTextureRect(floorTiles[i].tileImage);
		tileSprite.setPosition(floorTiles[i].position);
		tileSprite.setOrigin(25, 25);
		window.draw(tileSprite);
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