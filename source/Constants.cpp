#include "Constants.h"

const int Constants::tileSize = 50;
const float Constants::roomFriction = 0.7f;
const float Constants::pickupFriction = 0.001f;

int Constants::random(int min, int max) //Pass in range
{
    srand(time(NULL));  //srand() seeds rand.
    int r = rand() % (max - min) + min;
    return r;
}