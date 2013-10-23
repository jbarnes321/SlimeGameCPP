#include "Manifold.h"

Manifold::Manifold(Body *a, Body *b)
{
    A = a;
    B = b;
}

void Manifold::Initialize()
{
    //calculate average restitution
    e = std::min(A->restitution, B->restitution);

    //calculate static and dynamic friction
    sf = sqrt(A->staticFriction * B->staticFriction);
    df = sqrt(A->dynamicFriction * B->dynamicFriction);
}


void Manifold::applyImpulse()
{
    //0 mass means the body is static and cannont be moved
    if (A->massData.inv_mass == 0 && B->massData.inv_mass == 0)
    {
        infiniteMassCorrection();
        return;
    }

    for (int i = 0; i < contactCount; i++)
    {
        sf::Vector2f relVelocity = B->velocity - A->velocity;

        //Finds out if the objects are moving towards each other.
        //We only need to resolve collisions that are moving towards, not away.
        float velAlongNormal = PhysicsMath::DotProduct(relVelocity, normal);
        if (velAlongNormal > 0)
            return;

        float j = -(1 + e) * velAlongNormal;
        j /= (A->massData.inv_mass + B->massData.inv_mass);

        sf::Vector2f impulse = j * normal;
        A->velocity -= A->massData.inv_mass * impulse;
        B->velocity += B->massData.inv_mass * impulse;
    }
}

void Manifold::positionalCorrection()
{
    const float k_slop = 0.05f; // Penetration allowance
    const float percent = 0.5f; // Penetration percentage to correct
    sf::Vector2f correction = (std::max( penetration - k_slop, 0.0f ) /
                         (A->massData.inv_mass + B->massData.inv_mass)) * normal * percent;

    A->position -= correction * A->massData.inv_mass;
    B->position += correction * B->massData.inv_mass;
}

void Manifold::infiniteMassCorrection()
{
    A->velocity = sf::Vector2f(0, 0);
    B->velocity = sf::Vector2f(0, 0);
}

void Manifold::AABBvsAABB()
{
    contactCount = 0;


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
                    normal.x = -1;
                else
                    normal.x = 1;

                normal.y = 0;
                penetration = xOverlap;
                contactCount++;
                return;
            }
            else
            {
                if (n.y < 0)
                    normal.y = -1;
                else
                    normal.y = 1;

                normal.x = 0;
                penetration = yOverlap;
                contactCount++;
                return;
            }
        }
    }
}