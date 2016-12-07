#include "G_Miscfuncandvar.h"

float G_Miscfuncandvar::getRandomNumber()
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(-750, 750); // define the range
    randomNumber = distr(eng);
    return randomNumber;
}

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
