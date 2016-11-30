#include "include/G_Miscfuncandvar.h"

//Calculate a quadratic equation
sf::Vector2f G_Miscfuncandvar::calculateQuadratic(float n)
{
    sf::Vector2f tempVector;
    float y = 370 + (2.2 * (std::pow(n, 2)) / 800);
    float x = 390 + n;
    tempVector.x = x;
    tempVector.y = y;
    return tempVector;
}
