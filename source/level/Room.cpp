#include "Room.h"

Room::Room()
{

}


Room::Room(int r, int c, RoomType type, std::string mName, int ID, std::string levelType, Room (*levelRoomPtr)[10])
{
	row = r;
	col = c;
    roomID = ID;
    roomType = type;
	levelPosition = sf::Vector2i(c, r);	//the position on the minimap, rows = y, col = x
	mapName = mName;
	levelDir = "assets/level/" + levelType + "/";
	lvlRoomPtr = levelRoomPtr;
	unlocked = false;
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

				//cellMap[j][i] = Cell(tileID, j, i);

				if (tileID == '#')//edge of the room wall
				{
					//create a new wall and add it to wallsInRoom
					Wall newWall(tempVector, levelDir + "tileFloorSpriteSheet", false, false, 
								sf::IntRect(3 * Constants::tileSize, 0, Constants::tileSize, Constants::tileSize));
					newWall.LoadContent(tileSheetTexture);
					wallsInRoom.push_back(newWall);

					//create a tile underneath the wall
					temp.tileID = Constants::random(0, 3);
					temp.tileImage = sf::IntRect((temp.tileID % 4) * Constants::tileSize, 
												(temp.tileID / 4) * Constants::tileSize, Constants::tileSize, Constants::tileSize);

				}
				else if (tileID == '|')//normal walls
				{
					//create a new wall and add it to wallsInRoom
					Wall newWall(tempVector, levelDir + "tileFloorSpriteSheet", false, true, 
								sf::IntRect(3 * Constants::tileSize, 0, Constants::tileSize, Constants::tileSize));
					newWall.LoadContent(tileSheetTexture);
					wallsInRoom.push_back(newWall);

					//create a tile underneath the wall
					temp.tileID = Constants::random(0, 3);
					temp.tileImage = sf::IntRect((temp.tileID % 4) * Constants::tileSize, 
												(temp.tileID / 4) * Constants::tileSize, Constants::tileSize, Constants::tileSize);
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

	if (enemiesInRoom.size() == 0 && unlocked == false)
    {
        unlockDoors();
        //dropPickup();
    }

}


void Room::Draw(sf::RenderWindow &window)
{
	//draw every Tile in the room
	for(std::vector<int>::size_type i = 0; i != floorTiles.size(); i++)
	{
		sf::Sprite tileSprite;
		tileSprite.setTexture(tileSheetTexture);
		tileSprite.setTextureRect(floorTiles[i].tileImage);
		tileSprite.setPosition(floorTiles[i].position);
		tileSprite.setOrigin(25, 25);
		window.draw(tileSprite);
	}

	

	//draw all the walls in the room
	for(std::vector<int>::size_type i = 0; i != wallsInRoom.size(); i++)
	{
		wallsInRoom[i].Draw(window);
	}

	drawBorders(window);

	for(std::vector<int>::size_type i = 0; i != doorsInRoom.size(); i++)
	{
        if (!checkDoorDirection(doorsInRoom[i].doorDirection))
			doorsInRoom[i].Draw(window);
    }
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

void Room::createDoors(std::string &levelType, sf::Texture *doorTextures)
{
	Room topRoom, bottomRoom, leftRoom, rightRoom;
	Door topDoor, bottomDoor, leftDoor, rightDoor;

	sf::IntRect topClosedSource = sf::IntRect(0, 0, 100, 50);
    sf::IntRect bottomClosedSource = sf::IntRect(0, 0, 100, 50);
    sf::IntRect leftClosedSource = sf::IntRect(0, 0, 50, 100);
    sf::IntRect rightClosedSource = sf::IntRect(0, 0, 50, 100);
    sf::IntRect topOpenSource = sf::IntRect(0, 50, 100, 50);
    sf::IntRect bottomOpenSource = sf::IntRect(0, 50, 100, 50);
    sf::IntRect leftOpenSource = sf::IntRect(0, 50, 50, 100);
    sf::IntRect rightOpenSource = sf::IntRect(0, 100, 50, 100);

	//create the door for the top side of the room
	if (row != 0 && lvlRoomPtr[row - 1][col].roomID != -1)
    {
        topRoom = lvlRoomPtr[row - 1][col];

        if (topRoom.roomType == BOSS || roomType == BOSS)
        {
            topClosedSource = sf::IntRect(Constants::tileSize * 8, 0, Constants::tileSize * 2, Constants::tileSize);
            topOpenSource = sf::IntRect(Constants::tileSize * 8, Constants::tileSize, Constants::tileSize * 2, Constants::tileSize);
        }
        else if (topRoom.roomType == SHOP || roomType == SHOP)
        {
            topClosedSource = sf::IntRect(Constants::tileSize * 2, 0, Constants::tileSize * 2, Constants::tileSize);
            topOpenSource = sf::IntRect(Constants::tileSize * 2, Constants::tileSize, Constants::tileSize * 2, Constants::tileSize);
        }
        else if (topRoom.roomType == TREASURE || roomType == TREASURE)
        {
            topClosedSource = sf::IntRect(Constants::tileSize * 4, 0, Constants::tileSize * 2, Constants::tileSize);
            topOpenSource = sf::IntRect(Constants::tileSize * 4, Constants::tileSize, Constants::tileSize * 2, Constants::tileSize);
        }
        else if (topRoom.roomType == LASTROOM || roomType == LASTROOM)
        {
            topClosedSource = sf::IntRect(Constants::tileSize * 6, 0, Constants::tileSize * 2, Constants::tileSize);
            topOpenSource = sf::IntRect(Constants::tileSize * 6, Constants::tileSize, Constants::tileSize * 2, Constants::tileSize);
        }
        else//normal or first room
        {
            topClosedSource = sf::IntRect(0, 0, Constants::tileSize * 2, Constants::tileSize);
            topOpenSource = sf::IntRect(0, Constants::tileSize, Constants::tileSize * 2, Constants::tileSize);
        }

        topDoor = Door(sf::Vector2f(400, 75), topOpenSource, topClosedSource, 
						getDoorState(Door::UP), Door::UP);
		topDoor.LoadContent(doorTextures[0]);
        doorsInRoom.push_back(topDoor);
    }

	 //create the door for the bottom side of the room
	if (row != 7 && lvlRoomPtr[row + 1][col].roomID != -1)
    {
        bottomRoom = lvlRoomPtr[row + 1][col];

        if (bottomRoom.roomType == BOSS || roomType == BOSS)
        {
            bottomClosedSource = sf::IntRect(Constants::tileSize * 8, 0, Constants::tileSize * 2, Constants::tileSize);
            bottomOpenSource = sf::IntRect(Constants::tileSize * 8, Constants::tileSize, Constants::tileSize * 2, Constants::tileSize);
        }
        else if (bottomRoom.roomType == SHOP || roomType == SHOP)
        {
            bottomClosedSource = sf::IntRect(Constants::tileSize * 2, 0, Constants::tileSize * 2, Constants::tileSize);
            bottomOpenSource = sf::IntRect(Constants::tileSize * 2, Constants::tileSize, Constants::tileSize * 2, Constants::tileSize);
        }
        else if (bottomRoom.roomType == TREASURE || roomType == TREASURE)
        {
            bottomClosedSource = sf::IntRect(Constants::tileSize * 4, 0, Constants::tileSize * 2, Constants::tileSize);
            bottomOpenSource =sf::IntRect(Constants::tileSize * 4, Constants::tileSize, Constants::tileSize * 2, Constants::tileSize);
        }
        else if (bottomRoom.roomType == LASTROOM || roomType == LASTROOM)
        {
            bottomClosedSource = sf::IntRect(Constants::tileSize * 6, 0, Constants::tileSize * 2, Constants::tileSize);
            bottomOpenSource = sf::IntRect(Constants::tileSize * 6, Constants::tileSize, Constants::tileSize * 2, Constants::tileSize);
        }
        else//normal or first room
        {
            bottomClosedSource = sf::IntRect(0, 0, Constants::tileSize * 2, Constants::tileSize);
            bottomOpenSource = sf::IntRect(0, Constants::tileSize, Constants::tileSize * 2, Constants::tileSize);
        }

        bottomDoor = Door(sf::Vector2f(400, 625), bottomOpenSource, bottomClosedSource,
							getDoorState(Door::DOWN), Door::DOWN);
		bottomDoor.LoadContent(doorTextures[1]);
        doorsInRoom.push_back(bottomDoor);
    }

	//create the door for the left side of the room
	if (col != 0 && lvlRoomPtr[row][col - 1].roomID != -1)
    {
        leftRoom = lvlRoomPtr[row][col - 1];

        if (leftRoom.roomType == BOSS || roomType == BOSS)
        {
            leftClosedSource = sf::IntRect(Constants::tileSize * 4, 0, Constants::tileSize, Constants::tileSize * 2);
            leftOpenSource = sf::IntRect(Constants::tileSize * 4, Constants::tileSize * 2, Constants::tileSize, Constants::tileSize * 2);
        }
        else if (leftRoom.roomType == SHOP || roomType == SHOP)
        {
            leftClosedSource = sf::IntRect(Constants::tileSize, 0, Constants::tileSize, Constants::tileSize * 2);
            leftOpenSource = sf::IntRect(Constants::tileSize, Constants::tileSize * 2, Constants::tileSize, Constants::tileSize * 2);
        }
        else if (leftRoom.roomType == TREASURE || roomType == TREASURE)
        {
            leftClosedSource = sf::IntRect(Constants::tileSize * 2, 0, Constants::tileSize, Constants::tileSize * 2);
            leftOpenSource = sf::IntRect(Constants::tileSize * 2, Constants::tileSize * 2, Constants::tileSize, Constants::tileSize * 2);
        }
        else if (leftRoom.roomType == LASTROOM || roomType == LASTROOM)
        {
            leftClosedSource = sf::IntRect(Constants::tileSize * 3, 0, Constants::tileSize, Constants::tileSize * 2);
            leftOpenSource = sf::IntRect(Constants::tileSize * 3, Constants::tileSize * 2, Constants::tileSize, Constants::tileSize * 2);
        }
        else//normal or first room
        {
            leftClosedSource = sf::IntRect(0, 0, Constants::tileSize, Constants::tileSize * 2);
			leftOpenSource = sf::IntRect(0, Constants::tileSize * 2, Constants::tileSize, Constants::tileSize * 2);
        }

        leftDoor = Door(sf::Vector2f(25, 350), leftOpenSource, leftClosedSource,
						getDoorState(Door::LEFT), Door::LEFT);
		leftDoor.LoadContent(doorTextures[2]);
        doorsInRoom.push_back(leftDoor);
    }

    //create the door for the right side of the room
    if (col != 9 && lvlRoomPtr[row][col + 1].roomID != -1)
    {
        rightRoom = lvlRoomPtr[row][col + 1];

        if (rightRoom.roomType == BOSS || roomType == BOSS)
        {
            rightClosedSource = sf::IntRect(Constants::tileSize * 4, 0, Constants::tileSize, Constants::tileSize * 2);
            rightOpenSource = sf::IntRect(Constants::tileSize * 4, Constants::tileSize * 2, Constants::tileSize, Constants::tileSize * 2);
        }
        else if (rightRoom.roomType == SHOP || roomType == SHOP)
        {
            rightClosedSource = sf::IntRect(Constants::tileSize, 0, Constants::tileSize, Constants::tileSize * 2);
            rightOpenSource = sf::IntRect(Constants::tileSize, Constants::tileSize * 2, Constants::tileSize, Constants::tileSize * 2);
        }
        else if (rightRoom.roomType == TREASURE || roomType == TREASURE)
        {
            rightClosedSource = sf::IntRect(Constants::tileSize * 2, 0, Constants::tileSize, Constants::tileSize * 2);
            rightOpenSource = sf::IntRect(Constants::tileSize * 2, Constants::tileSize * 2, Constants::tileSize, Constants::tileSize * 2);
        }
        else if (rightRoom.roomType == LASTROOM || roomType == LASTROOM)
        {
            rightClosedSource = sf::IntRect(Constants::tileSize * 3, 0, Constants::tileSize, Constants::tileSize * 2);
            rightOpenSource = sf::IntRect(Constants::tileSize * 3, Constants::tileSize * 2, Constants::tileSize, Constants::tileSize * 2);
        }
        else//normal or first room
        {
            rightClosedSource = sf::IntRect(0, 0, Constants::tileSize, Constants::tileSize * 2);
			rightOpenSource = sf::IntRect(0, Constants::tileSize * 2, Constants::tileSize, Constants::tileSize * 2);
        }

        rightDoor = Door(sf::Vector2f(775, 350), rightOpenSource, rightClosedSource,
						getDoorState(Door::RIGHT), Door::RIGHT);
		rightDoor.LoadContent(doorTextures[3]);
        doorsInRoom.push_back(rightDoor);
    }
}


Door::DoorState Room::getDoorState(Door::DoorDirection direction)
{
	int iRow = row;
    int iCol = col;

    if (direction == Door::UP)
        iRow--;
    else if (direction == Door::DOWN)
        iRow++;
    else if (direction == Door::LEFT)
        iCol--;
    else if (direction == Door::RIGHT)
        iCol++;
            
    if(!checkDoorDirection(direction))
    {
        if (lvlRoomPtr[iRow][iCol].roomType == LASTROOM)
            return Door::PORTALCLOSED;

        else if (lvlRoomPtr[iRow][iCol].roomType == TREASURE)
            return Door::LOCKEDCLOSED;
    }

    return Door::CLOSED; 
}

bool Room::checkDoorDirection(Door::DoorDirection doorDirection)
{
	if (doorDirection == Door::UP)
	{
		if (row == 0)
			return true;
		else if (lvlRoomPtr[row - 1][col].roomID == -1)
			return true;
	}

	if (doorDirection == Door::DOWN)
	{
		if (row == 7)
			return true;
		else if (lvlRoomPtr[row + 1][col].roomID == -1)
			return true;
	}

	if (doorDirection == Door::LEFT)
	{
		if (col == 0)
			return true;
		else if (lvlRoomPtr[row][col - 1].roomID == -1)
			return true;
	}

	if (doorDirection == Door::RIGHT)
	{
		if (col == 9)
			return true;
		else if (lvlRoomPtr[row][col + 1].roomID == -1)
			return true;
	}

	return false;
}

void Room::unlockDoors()
{
    for(std::vector<int>::size_type i = 0; i != doorsInRoom.size(); i++)
	{
        if (doorsInRoom[i].doorState == Door::LOCKEDCLOSED)                   
            doorsInRoom[i].doorState = Door::LOCKEDOPEN;

        else if (doorsInRoom[i].doorState == Door::PORTALCLOSED)
            doorsInRoom[i].doorState = Door::PORTALOPEN;
                
        if(checkDoorDirection(doorsInRoom[i].doorDirection) == false)
		{
            if (doorsInRoom[i].doorState == Door::CLOSED)
            {
                doorsInRoom[i].doorState = Door::OPEN;
                doorsInRoom[i].currentSource = doorsInRoom[i].openSource;
                doorsInRoom[i].body.layer = 7;
            }
		}
    }

    unlocked = true;
}