#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <cstdlib> //to use random numbers
#include <ctime>   //to use random numbers

class Constants
{
    public:
        static const int tileSize;
        static const float roomFriction;
        static const float pickupFriction;

        static int random(int max, int min); //Pass in range
};

#endif // CONSTANTS_H_INCLUDED
