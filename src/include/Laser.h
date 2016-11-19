#ifndef LASER_H
#define LASER_H

#include <SFML/Graphics.hpp>

class Laser
{
    public:
        Laser();

        //A boolean value to determine
        //when the laser is in use
        bool isLaserOn = false;

        //Damage the laser should do
        float laserDamage = 0.025;

        //Our laser sprite
        sf::Sprite laserSprite;

        //Grab the width/height
        int getWidth() { return laserTexture.getSize().x; }
        int getHeight() { return laserTexture.getSize().y; }

    private:
        sf::Texture laserTexture;
};

#endif // LASER_H
