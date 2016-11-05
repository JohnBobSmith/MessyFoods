#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet
{
    public:
        //Set our textures up automatically
        Bullet();

        //The sprite to be drawn
        sf::Sprite bulletSprite;

        //Velocities and positions
        float velocityX = 0;
        float velocityY = 0;
        float positionX = 0;
        float positionY = 0;

        //do we render this bullet?
        bool isActive = false;

        //Bullets event bullet has a velocity
        const float bulletVelocity = 75.0f;

        //Every bullet does damage
        const int bulletDamage = 12;

        //Cap our rate of fire
        //Change this to change the rate of fire
        const float maxRateOfFire = 0.45;

        //Our working rate of fire which we
        //can do stuff to
        float rateOfFire = maxRateOfFire;

        //Self explanatory. Allow us to grab the texture/sprite width and height
        int getWidth() { return bulletTexture.getSize().x; }
        int getHeight() { return bulletTexture.getSize().y; }

        //Expose the maximum amount of bullets allowed
        int getMaxBullets() { return maxBullets; };

    private:
        //Every bullet must have a texture
        sf::Texture bulletTexture;

        //Give our for-loops a boundary, and
        //prevent an excessive amount of bullets
        //from accumulating. Not intended to be changed
        //by anything, hence private and const.
        const int maxBullets = 200;
};

#endif // BULLET_H
