#include "Constants.h"

int Constants::random(int max, int min) //Pass in range
{
    srand(time(NULL));  //Changed from rand(). srand() seeds rand for you.
    int random = rand() % max + min;
    return random;
}
