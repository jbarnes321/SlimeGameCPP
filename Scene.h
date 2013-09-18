#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include "Manifold.h"
#include "Constants.h"

class Scene
{
    public:
        Scene(sf::Vector2f gravity);

        void step();

        void addBodyCurrent(Body *b);

        void removeBodyCurrent(Body *b);

        sf::Vector2f gravity;

        std::vector<Body*> currentRoomBodies;

        std::vector<Manifold> contacts;

    private:

        void integrateForces(Body *b);

        void constantFrictionForce(Body *b);

        void integrateVelocity(Body *b);
};


#endif // SCENE_H_INCLUDED
