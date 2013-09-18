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

void Manifold::solve()
{

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
