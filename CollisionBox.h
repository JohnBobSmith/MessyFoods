#ifndef COLLISIONBOX_H
#define COLLISIONBOX_H

#include <SFML/Graphics.hpp>

class CollisionBox
{
    public:
        //Check axis aligned bounding box collision
        /*
            xA = object A's x position
            yA = object A's y position
            wA = width of A
            hA = height of A
            Repeat for B values
        */
        bool checkAABBcollision(float xA, float yA, float wA, float hA, float xB, float yB, float wB, float hB);
};

#endif // COLLISIONBOX_H
