#ifndef OCEAREAL_H
#define OCEAREAL_H

#include <SFML/Graphics.hpp>

class Cereal
{
    public:
        //Set our textures up automatically
        Cereal();

        //The sprite to be drawn
        sf::Sprite cerealSprite;

        //Velocities and positions
        float velocityX = 0;
        float velocityY = 0;
        float positionX = 0;
        float positionY = 0;

        //do we render (eat) this cereal piece?
        bool isActive = false;

        //Every cereal has a velocity
        const float cerealVelocity = 75.0f;

        //Every cereal does damage
        const int cerealDamage = 12;

        //Cap our rate of fire
        //Change this to change the rate of fire
        const float maxRateOfFire = 0.45;

        //Our working rate of fire which we
        //can do stuff to
        float rateOfFire = maxRateOfFire;

        //Self explanatory. Allow us to grab the texture/sprite width and height
        int getWidth() { return cerealTexture.getSize().x; }
        int getHeight() { return cerealTexture.getSize().y; }

        //Expose the maximum amount of oceareals allowed
        int getMaxCereals() { return maxCereals; };

    private:
        //Every cereal must have a texture
        sf::Texture cerealTexture;

        //Give our for-loops a boundary, and
        //prevent an excessive amount of cereals/ocereal
        //from accumulating. Not intended to be changed
        //by anything, hence private and const.
        const int maxCereals = 200;
};

#endif // OCEAREAL_H
