#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <cstdlib> //to use random numbers
#include <ctime>   //to use random numbers

class Constants
{
    public:
        const int tileSize = 50;
        const float roomFriction = 0.7f;
        const float pickupFriction = 0.001f;

        static int random(int max, int min); //Pass in range
};

#endif // CONSTANTS_H_INCLUDED
