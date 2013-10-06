#include "LevelGenerator.h"

LevelGenerator::LevelGenerator()
{
}

LevelGenerator::LevelGenerator(Level::LevelType type, int difficulty, Room (*lvlRPtr)[10])
{
    levelType = type;
	levelDifficulty = difficulty;
	lvlRoomPtr = lvlRPtr;
}


// This function is going to generate the level map and hold the mini map
// information.
bool LevelGenerator::generateMap()
{
    int direction;
    int previousDirection;
    int maxLength;
    int maxRooms = 80;
    int roomBudget = budget();
    int specialBudget = getSpecials();
    sf::Vector2i tempPosition;
    sf::Vector2i differenceVector;
    std::vector<sf::Vector2i> lonelies;
	totalRoomCount = 10;

	//initialize every room in the level
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 10; j++)
        {
			lvlRoomPtr[i][j] = Room(i, j, Room::NONE, LevelTypeToString(levelType), -1, "none");
        }
    }

    // Creates the max length of rooms before turning, to create more rooms.
    maxLength = roomBudget / 3;
    if (maxLength == 0)
        maxLength = 1;

    // Remove special rooms from the roomBudget.
    roomBudget -= specialBudget;

    // Create start room and remove it from roomBudget;
    pickStartRoom();
    roomBudget--;
    previousDirection = 0;

    // This is the main loop that will generate rooms.  Squares are very
    // possible with this method of generation, but not as likely as before.
    while (roomBudget > 0 && maxRooms > 0)
    {
        maxRooms--;
        int length = Constants::random(2, maxLength);
        int count;

        direction = Constants::random(0, 4);
        count = 3;

        // This loop gives random a few chances to pick a different
        // direction as opposed to continuing in the same line.
        while (count > 0 && direction == previousDirection)
        {
            direction = Constants::random(0, 4);
            count--;
        }
        // This checks to see if that direction will be valid, sets the
        // previous direction to the current, gets the vector needed to
        // move in that direction.
        direction = checkDirection(direction, previousDirection, length);
        previousDirection = direction;
        differenceVector = getDifferenceVector(direction);

        // Sets tempPosition to current position and loops to create the
        // amount of rooms that length has stored.
        tempPosition = position;
        for (int i = 0; i < length; i++)
        {
            if (roomBudget <= 0)
                break;

            // Moves the tempPosition based on the differenceVector and
            // adds a room to the map.  Removes a room from the budget.
            tempPosition += differenceVector;

            // This checks if the current position is out of bounds.  If it is,
            // we undo the last move and break out of this loop to continue in a
            // new direction.
            if (outOfBounds(tempPosition))
            {
                tempPosition -= differenceVector;
                break;
            }

            // This makes sure we don't overwrite the startRoom.  Overwriting other
            // rooms are OK, it's what's going to give us a random amount of rooms
            // every time we run the program.
            if(tempPosition != startPos)
            {
                addRoom(tempPosition, Room::NORMAL);
                roomBudget--;
            }

            // Hard to explain in writing, but this determines if the
            // current position will change to one of the temp positions
            // that were created in this loop.
            if (Constants::random(0, 8) < 2)
                position = tempPosition;
        }
    }

    if (levelType != Level::Hub)
    {
        // Adds the boss room.
        lonelies = getLonelies();
        if (lonelies.size() == 0)
            return false;
        int temp = Constants::random(0, lonelies.size());
        addRoom(lonelies.at(temp), Room::BOSS);

        // Adds the treasure room.
        lonelies = getLonelies();
        if (lonelies.size() == 0)
            return false;
        temp = Constants::random(0, lonelies.size());
        addRoom(lonelies.at(temp), Room::TREASURE);

        // Adds portal room.
        lonelies = getLonelies();
        if (lonelies.size() == 0)
            return false;
        temp = Constants::random(0, lonelies.size());
        addRoom(lonelies.at(temp), Room::LASTROOM);

        // Adds shop room.
        lonelies = getLonelies();
        if (lonelies.size() == 0)
            return false;
        temp = Constants::random(0, lonelies.size());
        addRoom(lonelies.at(temp), Room::SHOP);
    }

    return true;
}


// Simple function to create a room at the current position with the
// specified room type.  Beats re-writing the same thing many times.
void LevelGenerator::addRoom(sf::Vector2i position, Room::RoomType roomType)
{
    int col = (int)position.x;
    int row = (int)position.y;

    int roomID = Constants::random(1, totalRoomCount + 1);

    if(roomType == Room::BOSS)
		lvlRoomPtr[row][col] = Room(row, col, Room::BOSS, specialRoomDir, 0, LevelTypeToString(levelType));

    else if (roomType == Room::SHOP)
        lvlRoomPtr[row][col] = Room(row, col, Room::SHOP, specialRoomDir, 1, LevelTypeToString(levelType));

    else if(roomType == Room::TREASURE)
        lvlRoomPtr[row][col] = Room(row, col, Room::TREASURE, specialRoomDir, 0, LevelTypeToString(levelType));

    else if (roomType == Room::LASTROOM)
        lvlRoomPtr[row][col] = Room(row, col, Room::LASTROOM,specialRoomDir, 0, LevelTypeToString(levelType));

    else
        lvlRoomPtr[row][col] = Room(row, col, Room::NORMAL,  mapFileDir, roomID, LevelTypeToString(levelType));
}

int LevelGenerator::getSpecials()
{
    int specialBudget = 4;

    return specialBudget;
}


std::vector<sf::Vector2i> LevelGenerator::getLonelies()
{
    std::vector<sf::Vector2i> lonelies;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            sf::Vector2i temp(j, i);

            //rooms with ID == -1 are empty/null rooms
            if (lvlRoomPtr[i][j].roomID == -1 && getAdjacentRoomCount(temp) == 1)
                lonelies.push_back(temp);
        }
    }

    return lonelies;
}


int LevelGenerator::getAdjacentRoomCount(sf::Vector2i position)
{
    int count = 0;
    int row = (int)position.y;
    int col = (int)position.x;

    // These if statements are going to check the rooms adjacent to the
    // current position. If that room is null, then it does nothing, but if
    // it isn't null, we add one to count.
    if (outOfBounds(sf::Vector2i(col, row + 1)) == false && lvlRoomPtr[row + 1][col].roomID != -1)
    {
        if (lvlRoomPtr[row + 1][col].roomType != Room::NORMAL)
        {
            return 4;
        }
        count++;
    }

    if (outOfBounds(sf::Vector2i(col, row - 1)) == false && lvlRoomPtr[row - 1][col].roomID != -1)
    {
        if (lvlRoomPtr[row - 1][col].roomType != Room::NORMAL)
            return 4;
        count++;

    }

    if (outOfBounds(sf::Vector2i(col + 1, row)) == false && lvlRoomPtr[row][col + 1].roomID != -1)
    {
        if (lvlRoomPtr[row][col + 1].roomType != Room::NORMAL)
            return 4;
        count++;
    }

    if (outOfBounds(sf::Vector2i(col - 1, row)) == false && lvlRoomPtr[row][col - 1].roomID != -1)
    {
        if (lvlRoomPtr[row][col - 1].roomType != Room::NORMAL)
            return 4;
        count++;
    }

    if (count == 0)
        return 4;

    return count;
}


void LevelGenerator::pickStartRoom()
{
    // Center of the level map.
    int col = 5;    // x coordinate
    int row = 4;    // y coordinate

    // Selects some random offset from the center of the level map.
    col = Constants::random(col - 2, col + 2);
    row = Constants::random(row - 2, row + 2);

    // Creates the HUB level.
    if(levelType == Level::Hub)
		lvlRoomPtr[row][col] = Room(row, col, Room::HUB, mapFileDir, 0, LevelTypeToString(levelType));

    // Creats the initial room, which is empty.
    else
        lvlRoomPtr[row][col] = Room(row, col, Room::FIRST, mapFileDir, 0, LevelTypeToString(levelType));

	startPos = sf::Vector2i(col, row);
    position = sf::Vector2i(col, row);
}

 // This function returns the number of rooms each floorType should have.
int LevelGenerator::budget()
{
    int value;
    // Switches between levelTypes and returns the roomBudget.

    if (levelType == Level::Hub)
        return 1;

    switch (levelDifficulty)
    {
        case 0:
            value = 25;
            break;
        case 1:
            value = 9;
            break;
        case 2:
            value = 12;
            break;
        case 3:
            value = 15;
            break;
        case 4:
            value = 18;
            break;
        case 5:
            value = 21;
            break;
        case 6:
            value = 23;
            break;
        case 7:
            value = 25;
            break;
        case 8:
            value = 27;
            break;
        case 9:
            value = 30;
            break;
        default:
            value = 9;
            break;
    }

    return value;

}


// This function checks if creating a room in the desired direction will
// result in an array out of bounds error. If so, generate new direction.
int LevelGenerator::checkDirection(int direction, int prev, int length)
{
    int count = 0;
    while (true)
    {
        if (getDifferenceVector(direction) == getDifferenceVector(prev) * -1)
            direction = Constants::random(0, 4);

        else if (count > 3 && direction == prev)
            direction = Constants::random(0, 4);

        // Neither of the above cases are true, so the direction is fine.
        else
            return direction;

        count++;
    }
}

 // This function creates a vector based on the direction variable.
// direction dictates in which direction we'll create a new room.
sf::Vector2i LevelGenerator::getDifferenceVector(int direction)
{
    switch (direction)
    {
        case 0:
            // Move Right.
            return sf::Vector2i(1, 0);
        case 1:
            // Move Left;
            return sf::Vector2i(-1, 0);
        case 2:
            // Move Down.
            return sf::Vector2i(0, 1);
        case 3:
            // Move Up.
            return sf::Vector2i(0, -1);

        // This should never happen, but it's required within a function.
        default:
            return sf::Vector2i(1, 0);
    }
}

bool LevelGenerator::outOfBounds(sf::Vector2i position)
{
    int col = (int)position.x;
    int row = (int)position.y;

    // Checks if the generator is out of bounds in the x direction.
    if (col >= 10 || col < 0)
        return true;

    // Checks if the generator is out of bounds in the y direction.
    if (row >= 8 || row < 0)
        return true;

    return false;
}

std::string LevelGenerator::LevelTypeToString(Level::LevelType type)
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