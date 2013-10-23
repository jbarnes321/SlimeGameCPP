#include "Scene.h"

Scene::Scene(sf::Vector2f grav)
{
    gravity = grav;
}

void Scene::step()
{
    contacts.clear();

    //look for collisions between bodies
    for(int i = 0; i < currentRoomBodies.size(); i++)
    {
        Body *A = currentRoomBodies[i];
        A->setAABB();

        for (int j = i + 1; j < currentRoomBodies.size(); j++)
        {
            Body *B = currentRoomBodies[j];

            /* Layer values
             * Player = 0
             * Player Bullets = 5
             * Enemies = 1
             * Enemy Bullets = 4
             * Walls/Doors = 2
             * Pickups = 3
             * XP = 6
             * open doors = 7
             */

             //skip collisions between player and player bullets
            if ((A->layer == 0 && B->layer == 5) || (A->layer == 5 && B->layer == 0))
                continue;
            //skip collisions between player bullets and enemy bullets
            if ((A->layer == 5 && B->layer == 4) || (A->layer == 4 && B->layer == 5))
                continue;
            //skip collisions between enemies and enemy bullets
            if ((A->layer == 1 && B->layer == 4) || (A->layer == 4 && B->layer == 1))
                continue;
            //skip collisions between flying enemies and walls
            if ((A->layer == 1 && B->layer == 2) || (A->layer == 2 && B->layer == 1))
            {
                if (A->isFlying || B->isFlying)
                    continue;
            }
            //skip collisions between walls and doors
            if (A->layer == 2 && B->layer == 2)
                continue;
            //skip collisions between enemies and pickups
            if ((A->layer == 1 && B->layer == 3) ||(A->layer == 3 && B->layer == 1))
                continue;
            //skip collisions between bullets and pickups
            if (((A->layer == 5 || A->layer == 4) && B->layer == 3) || (A->layer == 3 && (B->layer == 5 || A->layer == 4)))
                continue;
            //skip collisions with any xp, hazards
            if (A->layer == 6 || B->layer == 6)
                continue;
            //skip collisions with open doors except for pickups
            if (A->layer == 7 || B->layer == 7)
            {
                if (A->layer != 3 && B->layer != 3)
                    continue;
            }
            //skip collisions between two bodies with infinite mass
            if (A->massData.inv_mass == 0 && B->massData.inv_mass == 0)
                continue;

            //creates a relationship between Body A and B
            Manifold m(A, B);

            //check if Body A and B are colliding
			m.AABBvsAABB();

            //create a list of all colliding bodies
            if(m.contactCount > 0)
                contacts.push_back(m);
		}
	}

    //apply a negative force on all moving bodies. Purpose is to bring bodies to a stop
    //when no other forces are being applied. The friction value is Constants.roomFriction
    for (int i = 0; i < currentRoomBodies.size(); i++)
        constantFrictionForce(currentRoomBodies[i]);

    //give a velocity to all bodies that have a force applied to them.
    for (int i = 0; i < currentRoomBodies.size(); i++)
        integrateForces(currentRoomBodies[i]);

    //calculate the friction and restitution for each contact
    for (int i = 0; i < contacts.size(); i++)
        contacts[i].Initialize();

    //move the bodies so they are no longer colliding
    for (int i = 0; i < contacts.size(); i++)
        contacts[i].applyImpulse();

    //adjust each body's position based on its velocity
    for (int i = 0; i < currentRoomBodies.size(); i++)
        integrateVelocity(currentRoomBodies[i]);

    // Correct positions
    for (int i = 0; i < contacts.size(); i++)
        contacts[i].positionalCorrection();

    // Clear all forces
    for (int i = 0; i < currentRoomBodies.size(); i++)
    {
        Body *b = currentRoomBodies[i];
        b->force = sf::Vector2f(0, 0);
            
        
    }
}

void Scene::constantFrictionForce(Body *b)
{
    if (b->massData.inv_mass == 0.0f || b->isBullet)
        return;

	if (b->materialType == Body::PICKUP)
        b->force += (-b->velocity) * Constants::pickupFriction;
    else
        b->force += (-b->velocity) * Constants::roomFriction;
}

void Scene::integrateForces(Body *b)
{
    if (b->massData.inv_mass == 0.0f)
        return;

    if (b->force != sf::Vector2f(0, 0))
        b->velocity += (b->force * b->massData.inv_mass + gravity);
}

void Scene::integrateVelocity(Body *b)
{
    if (b->massData.inv_mass == 0.0f)
        return;

    b->position += b->velocity;
    integrateForces(b);
}

 void Scene::addBodyCurrent(Body *b)
{
	//add b to the vector if it is not already in the vector
	if (!(std::find(currentRoomBodies.begin(), currentRoomBodies.end(), b) != currentRoomBodies.end()))
	{
		currentRoomBodies.push_back(b);
	}

}

void Scene::removeBodyCurrent(Body *b)
{
	std::vector<Body*>::iterator position = std::find(currentRoomBodies.begin(), currentRoomBodies.end(), b);
	if (position != currentRoomBodies.end()) // == vector.end() means the element was not found
		currentRoomBodies.erase(position);
}