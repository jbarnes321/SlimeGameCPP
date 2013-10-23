#include "PhysicsMath.h"
#include <math.h>
#include <cmath>

float PhysicsMath::DotProduct(sf::Vector2f a, sf::Vector2f b)
{
    return (a.x * b.x) + (a.y * b.y);
}


//Finds the normal of 2 vectors
sf::Vector2f PhysicsMath::GetNormal(sf::Vector2f a, sf::Vector2f b)
{
    sf::Vector2f ret = b - a;
    ret = PhysicsMath::Normalize(ret);
    return ret;
}


//Calculates the normal vector
sf::Vector2f PhysicsMath::Normalize(sf::Vector2f source)
{
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
}