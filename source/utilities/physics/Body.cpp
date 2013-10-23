# include "Body.h"
Body::Body(){}


Body::Body(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f forc,
            MaterialType mType, int len, int hei, int lay)
{
    position = pos;
    velocity = vel;
    force = sf::Vector2f(0, 0);  //all bodies start with zero force applied in an direction
    length = len;       //the length of the bounding box
    height = hei;       //the height of the bounding box
    layer = lay;
    materialType = mType;
    setMaterial();          //sets the restitution based on the body's material type
    setAABB();              //sets the min and max the AABB
    staticFriction = 0.0f;
    dynamicFriction = 0.0f;
    isBullet = false;
    isFlying = false;
}

void Body::setMaterial()
{
    switch(materialType)
    {
    case PLAYER:
        setMassData(10);
        restitution = 0.0f;
        break;
    case WALL:
        setMassData(0);
        restitution = 0.5f;
        break;
    case DOOR:
        setMassData(0);
        restitution = 0;
        break;
    case ROCK:
        setMassData(0);
        restitution = 0;
        break;
    case WEAKENEMY:
        setMassData(5);
        restitution = 0;
        break;
    case NORMALENEMY:
        setMassData(12);
        restitution = 0;
        break;
    case STRONGENEMY:
        setMassData(15);
        restitution = 0;
        break;
    case BULLET:
        setMassData(1.5f);
        restitution = 0;
        break;
    case PICKUP:
        setMassData(0.1f);
        restitution = 0.5f;
        break;
    case XP:
        setMassData(2);
        restitution = 0.0f;
        break;
    default:
        setMassData(7);
        restitution = 0;
        break;
    }
}

void Body::setAABB()
{
    aabb.min = sf::Vector2f(position.x - length/2, position.y - height/2);
    aabb.max = sf::Vector2f(position.x + length/2, position.y + height/2);
    //this.boundingBox = new BoundingBox(new Vector3(aabb.min, 0), new Vector3(aabb.max, 0));
}

void Body::setMassData(float mass)
{
    massData.mass = mass;

    if (massData.mass == 0)
        massData.inv_mass = 0;
    else
        massData.inv_mass = 1 / massData.mass;
}

void Body::applyForce(float x, float y)
{
    force += sf::Vector2f(x, y);
}