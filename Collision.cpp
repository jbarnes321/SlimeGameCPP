#include "Collision.h"

void Collision::AABBvsAABB(Manifold *m)
{
    m->contactCount = 0;

    Body *A = m->A;
    Body *B = m->B;

    //Vector from A to B
    sf::Vector2f n = B->position - A->position;

    Body::AABB abox = A->aabb;
    Body::AABB bbox = B->aabb;

    // Calculate half extents along x axis for each object
    float aExtentX = (abox.max.x - abox.min.x) / 2;
    float bExtentX = (bbox.max.x - bbox.min.x) / 2;

     // Calculate overlap on x axis
    float xOverlap = aExtentX + bExtentX - abs(n.x);

    // SAT test on x axis
    if (xOverlap > 0)
    {
        // Calculate half extents along x axis for each object
        float aExtentY = (abox.max.y - abox.min.y) / 2;
        float bExtentY = (bbox.max.y - bbox.min.y) / 2;

        // Calculate overlap on y axis
        float yOverlap = aExtentY + bExtentY - abs(n.y);

        // SAT test on y axis
        if (yOverlap > 0)
        {
            // Find out which axis is axis of least penetration
            if (xOverlap < yOverlap)
            {
                if (n.x < 0)
                    m->normal.x = -1;
                else
                    m->normal.x = 1;

                m->normal.y = 0;
                m->penetration = xOverlap;
                m->contactCount++;
                return;
            }
            else
            {
                if (n.y < 0)
                    m->normal.y = -1;
                else
                    m->normal.y = 1;

                m->normal.x = 0;
                m->penetration = yOverlap;
                m->contactCount++;
                return;
            }
        }
    }
}
