#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include "Manifold.h"

class Collision
{
    public:
        static void AABBvsAABB(Manifold *m);
};
#endif // COLLISION_H_INCLUDED
