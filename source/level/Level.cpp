#include "Level.h"

Level::Level() {}

Level::Level(LevelType lType, int difficulty)
{
    levelType = lType;
    levelDifficulty = difficulty;
	drawEntireMap = true;
}


void Level::Initialize()
{
	
}


void Level::LoadContent()
{
	if(!mmbTexture.loadFromFile("assets/minimap/mapBackground.png"))
	{
		return;
	}
	if (levelType != Level::Hub && !mmrTexture.loadFromFile("assets/minimap/minimapSheet" + Level::LevelTypeToString(levelType) + ".png"))
	{
		return;
	}

	miniMapBackgroundSprite.setTexture(mmbTexture);
	miniMapBackgroundSprite.setPosition(800, 480);

	miniMapRoomSprite.setTexture(mmrTexture);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (levelRooms[i][j].roomID != -1)
			{
				levelRooms[i][j].LoadContent();
			}
		}
	}

}


void Level::Update()
{
    currentRoom->Update();
}


void Level::Draw(sf::RenderWindow &window)
{
     //draw the minimap, unless the current level is the hub
    if (levelType != Hub)
        drawMiniMap(window);

    currentRoom->Draw(window);
	
}


void Level::drawMiniMap(sf::RenderWindow &window)
{	
	window.draw(miniMapBackgroundSprite);

	//oldRooms are rooms the player has already visited
	//newRooms are all adjacent rooms to any old rooms

	levelRooms;

	if (drawEntireMap)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (levelRooms[i][j].roomID != -1)
				{
					sf::Sprite roomSprite;
					roomSprite.setPosition(j * 18.0f + 810, i * 14.0f + 500);
					roomSprite.setTexture(mmrTexture);
					roomSprite.setTextureRect(getMiniMapSprite(levelRooms[i][j].roomType, false));
					window.draw(roomSprite);
				}
				else
				{
					sf::Sprite roomSprite;
					roomSprite.setPosition(j * 18.0f + 810, i * 14.0f + 500);
					roomSprite.setTexture(mmrTexture);
					roomSprite.setTextureRect(getMiniMapSprite(levelRooms[i][j].roomType, true));
					window.draw(roomSprite);
				}
			}
		}
	}

	else
	{
	
	//if the current room is not already in oldRooms
	if (oldRooms.size() == 0)
		oldRooms.push_back(currentRoom);
	else if(!(std::find(oldRooms.begin(), oldRooms.end(), currentRoom) != oldRooms.end()))
		oldRooms.push_back(currentRoom);
	
	//make sure the current room isn't in newRooms
	if (newRooms.size() > 0)
	{
		if(std::find(newRooms.begin(), newRooms.end(), currentRoom) != newRooms.end())
		{
			newRooms.erase(std::remove(newRooms.begin(), newRooms.end(), currentRoom), newRooms.end());
		}
	}
	
	//find out which rooms are next to the current room
	adjacentMiniMapRooms(currentRoom->levelPosition);

	//draw all the new rooms
	if (newRooms.size() > 0)
	{	
		for(std::vector<int>::size_type i = 0; i != newRooms.size(); i++)
		{
			sf::Sprite roomSprite;
			roomSprite.setPosition(newRooms[i]->levelPosition.x * 18.0f + 810, newRooms[i]->levelPosition.y * 14.0f + 500);
			roomSprite.setTexture(mmrTexture);
			roomSprite.setTextureRect(getMiniMapSprite(newRooms[i]->roomType, true));
			window.draw(roomSprite);
		}
	}
	
	//draw all the old rooms
	for(std::vector<int>::size_type i = 0; i != oldRooms.size(); i++)
	{
		sf::Sprite roomSprite;
		roomSprite.setPosition(oldRooms[i]->levelPosition.x * 18.0f + 810, oldRooms[i]->levelPosition.y * 14.0f + 500);
		roomSprite.setTexture(mmrTexture);
		roomSprite.setTextureRect(getMiniMapSprite(oldRooms[i]->roomType, false));
		window.draw(roomSprite);
	}
	}
	
	//draw the current room
	sf::Sprite roomSprite;
	roomSprite.setPosition(currentRoom->levelPosition.x * 18.0f + 810, currentRoom->levelPosition.y * 14.0f + 500);
	roomSprite.setTexture(mmrTexture);
	roomSprite.setTextureRect(sf::IntRect(0, 0, 18, 14));
	window.draw(roomSprite);
 
}


sf::IntRect Level::getMiniMapSprite(Room::RoomType type, bool flag)
{
	switch (type)
	{
	case Room::TREASURE:
		return sf::IntRect(54, 0, 18, 14);
	case Room::LASTROOM:
		return sf::IntRect(72, 0, 18, 14);
	case Room::BOSS:
		return sf::IntRect(90, 0, 18, 14);
	case Room::SHOP:
		return sf::IntRect(108, 0, 18, 14);
	}

	if (flag)
		return sf::IntRect(36, 0, 18, 14);
	else
		return sf::IntRect(18, 0, 18, 14);
}


void Level::adjacentMiniMapRooms(sf::Vector2i roomPosition)
{
	
	int row = roomPosition.x;
	int col = roomPosition.y;


	//west room
	if (row - 1 >= 0 && levelRooms[row - 1][col].roomID != -1)
	{
		if (newRooms.size() > 0)
		{
			if (!(std::find(newRooms.begin(), newRooms.end(), &levelRooms[row - 1][col]) != newRooms.end()))
			{
				if (oldRooms.size() > 0)
				{
					if (!(std::find(oldRooms.begin(), oldRooms.end(), &levelRooms[row - 1][col]) != oldRooms.end()))
					{
						newRooms.push_back(&levelRooms[row - 1][col]);
					}
				}
				else
				{
					newRooms.push_back(&levelRooms[row - 1][col]);
				}
			}
		}
		else if (oldRooms.size() > 0)
		{
			if (!(std::find(oldRooms.begin(), oldRooms.end(), &levelRooms[row - 1][col]) != oldRooms.end()))
			{
				newRooms.push_back(&levelRooms[row - 1][col]);
			}
		}
		else
		{
			newRooms.push_back(&levelRooms[row - 1][col]);
		}
	}
	
	//north room
	if (row - 1 >= 0 && levelRooms[row - 1][col].roomID != -1)
	{
		if (newRooms.size() > 0)
		{
			if (!(std::find(newRooms.begin(), newRooms.end(), &levelRooms[row][col - 1]) != newRooms.end()))
			{
				if (oldRooms.size() > 0)
				{
					if (!(std::find(oldRooms.begin(), oldRooms.end(), &levelRooms[row][col - 1]) != oldRooms.end()))
					{
						newRooms.push_back(&levelRooms[row][col - 1]);
					}
				}
				else
				{
					newRooms.push_back(&levelRooms[row][col - 1]);
				}
			}
		}
		else if (oldRooms.size() > 0)
		{
			if (!(std::find(oldRooms.begin(), oldRooms.end(), &levelRooms[row][col - 1]) != oldRooms.end()))
			{
				newRooms.push_back(&levelRooms[row][col - 1]);
			}
		}
		else
		{
			newRooms.push_back(&levelRooms[row][col - 1]);
		}
	}

	//south room
	if (row - 1 >= 0 && levelRooms[row][col + 1].roomID != -1)
	{
		if (newRooms.size() > 0)
		{
			if (!(std::find(newRooms.begin(), newRooms.end(), &levelRooms[row][col + 1]) != newRooms.end()))
			{
				if (oldRooms.size() > 0)
				{
					if (!(std::find(oldRooms.begin(), oldRooms.end(), &levelRooms[row][col + 1]) != oldRooms.end()))
					{
						newRooms.push_back(&levelRooms[row][col + 1]);
					}
				}
				else
				{
					newRooms.push_back(&levelRooms[row][col + 1]);
				}
			}
		}
		else if (oldRooms.size() > 0)
		{
			if (!(std::find(oldRooms.begin(), oldRooms.end(), &levelRooms[row][col + 1]) != oldRooms.end()))
			{
				newRooms.push_back(&levelRooms[row][col + 1]);
			}
		}
		else
		{
			newRooms.push_back(&levelRooms[row][col + 1]);
		}
	}


	
	//east room
	if (row - 1 >= 0 && levelRooms[row + 1][col].roomID != -1)
	{
		if (newRooms.size() > 0)
		{
			if (!(std::find(newRooms.begin(), newRooms.end(), &levelRooms[row + 1][col]) != newRooms.end()))
			{
				if (oldRooms.size() > 0)
				{
					if (!(std::find(oldRooms.begin(), oldRooms.end(), &levelRooms[row + 1][col]) != oldRooms.end()))
					{
						newRooms.push_back(&levelRooms[row + 1][col]);
					}
				}
				else
				{
					newRooms.push_back(&levelRooms[row + 1][col]);
				}
			}
		}
		else if (oldRooms.size() > 0)
		{
			if (!(std::find(oldRooms.begin(), oldRooms.end(), &levelRooms[row + 1][col]) != oldRooms.end()))
			{
				newRooms.push_back(&levelRooms[row + 1][col]);
			}
		}
		else
		{
			newRooms.push_back(&levelRooms[row + 1][col]);
		}
	}
}

std::string Level::LevelTypeToString(Level::LevelType type)
{
	switch (type)
	{
		case Level::Hub :
			return "Hub";
		case Level::Start :
			return "Start";
		case Level::Fire :
			return "Fire";
		case Level::Ice :
			return "Ice";
		case Level::Poison :
			return "Poison";
		case Level::Ghost :
			return "Ghost";
		case Level::Electric :
			return "Electric";
		case Level::Earth :
			return "Earth";
		case Level::Necro :
			return "Necro";
		default :
			return "";
	}
}