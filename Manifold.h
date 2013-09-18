#ifndef MANIFOLD_H_INCLUDED
#define MANIFOLD_H_INCLUDED

#include <algorithm>

#include "Body.h"
#include "PhysicsMath.h"

class Manifold
{
    public:
        Manifold(Body *A, Body *B);

        void Initialize();

        void solve();

        void applyImpulse();

        void positionalCorrection();

        void infiniteMassCorrection();

        Body *A;
        Body *B;
        float penetration;      //Depth of penetration from collision
        sf::Vector2f normal;
        int contactCount;       //number of contacts that occurred during collision
        float e;                // Mixed restitution
        float df;               // Mixed dynamic friction
        float sf;               // Mixed static friction

    private:

};

#endif // MANIFOLD_H_INCLUDED
