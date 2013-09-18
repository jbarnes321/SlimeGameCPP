#ifndef PHYSICSMATH_H_INCLUDED
#define PHYSICSMATH_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <math.h>

class PhysicsMath
{
    public:
        static float DotProduct(sf::Vector2f a, sf::Vector2f b);

        static sf::Vector2f GetNormal(sf::Vector2f a, sf::Vector2f b);

        static sf::Vector2f Normalize(sf::Vector2f source);
};

#endif // PHYSICSMATH_H_INCLUDED
