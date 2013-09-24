#include "Constants.h"

const int Constants::tileSize = 50;
const float Constants::roomFriction = 0.7f;
const float Constants::pickupFriction = 0.001f;

int Constants::random(int max, int min) //Pass in range
{
    srand(time(NULL));  //Changed from rand(). srand() seeds rand for you.
    int random = rand() % max + min;
    return random;
}
