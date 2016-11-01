#include "include/CollisionBox.h"

bool CollisionBox::checkAABBcollision(float xA, float yA, float wA, float hA, float xB, float yB, float wB, float hB)
{
    //Axis aligned bounding box collision detection.
    //Which side of the box are we on?
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;

    //Assign the sides for A...
    leftA = xA;
    rightA = xA + wA;
    topA = yA;
    bottomA = yA + hA;

    //...and B
    leftB = xB;
    rightB = xB + wB;
    topB = yB;
    bottomB = yB + hB;

    //If bottomA floatersects topB
    if(bottomA <= topB){
        return false;
    }

    //If topA floatersects bottomB
    if(topA >= bottomB){
        return false;
    }

    //If rightA floatersects leftB
    if(rightA <= leftB){
        return false;
    }

    //If leftA floatersects rightB
    if(leftA >= rightB){
        return false;
    }

    //Not sure why this is required...
    return true;
}

