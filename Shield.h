#ifndef SHIELD_H
#define SHIELD_H

#include <SFML/Graphics.hpp>

class Shield
{
    public:
        //Automatic textures
        Shield();

        //Sprite
        sf::Sprite shieldSprite;

        //Velocities and positions
        float velocityX = 0;
        float velocityY = 0;
        float positionX = 0;
        float positionY = 0;

        //Is the shield running?
        bool isShieldUp = false;

        //Grab the width and height of our sprite
        int getWidth() { return shieldTexture.getSize().x; }
        int getHeight() { return shieldTexture.getSize().y; }

        //Return the max amount of shield segments
        int getMaxShieldBlocks() { return maxShieldBlocks; }

    private:
        sf::Texture shieldTexture;

        const int maxShieldBlocks = 60;
};

#endif // SHIELD_H
