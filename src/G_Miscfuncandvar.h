#ifndef G_MISCFUNCANDVAR_H
#define G_MISCFUNCANDVAR_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>

/*
    Global miscellaneous functions and variables
    G     _Misc          func      and var

    Store our global variables and a few things that
    dont fit anywhere else (hence the misc part of the
    class name). The value of PI, screen dimensions and
    our function for calculating quadratic curves are
    examples of stuff that fits here.
*/

class G_Miscfuncandvar
{
    public:
        //Our pi value
        constexpr double pi_value() { return M_PI; }
        const double pi = pi_value();

        //Screen dimensions
        const int screenWidth = 800;
        const int screenHeight = 600;

        //Calculate a quadratic equation, for our shields
        sf::Vector2f calculateQuadratic(float n);

        //Grab a random number from our RNG
        float getRandomNumber();

    private:
        //The random number to return, from our RNG.
        float randomNumber;
};

#endif // G_MISCFUNCANDVAR_H
