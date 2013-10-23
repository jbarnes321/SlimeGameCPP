#ifndef BODY_H_INCLUDED
#define BODY_H_INCLUDED

#include <SFML/Graphics.hpp>

class Body
{
    public:

         //material type determines each objects mass and restitution
        enum MaterialType
        {
            PLAYER,
            ROCK,
            WALL,
            DOOR,
            WEAKENEMY,
            NORMALENEMY,
            STRONGENEMY,
            BULLET,
            PICKUP,
            XP
        } materialType;

        //default constructor
        Body();

        Body(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f force,
             MaterialType materialType, int length, int height, int layers);

        void setAABB();

        void setMassData(float mass);

        void applyForce(float x, float y);

        struct MassData
        {
            float mass;
            float inv_mass;
        };


        //Bounding Box
        struct AABB
        {
            sf::Vector2f min;    //top left of bounding box
            sf::Vector2f max;    //bottom right of bounding box
        };

        sf::Vector2f velocity;
        sf::Vector2f force;
        sf::Vector2f position;
        int length;
        int height;
        int layer;
        MassData massData;
        AABB aabb;
        float staticFriction;
        float dynamicFriction;
        bool isBullet;
        bool isFlying;
        float restitution;
        //BoundingBox boundingBox;

    private :
         void setMaterial();


};
#endif // BODY_H_INCLUDED