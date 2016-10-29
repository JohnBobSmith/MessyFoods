#include <SFML/Graphics.hpp>
#include "Shield.h"
#include <iostream>

Shield::Shield()
{
    if (!shieldTexture.loadFromFile("textures/shield.png")) {
        std::cout << "Error, missing shield texture...\n";
    }
    shieldSprite.setTexture(shieldTexture);
}

void Shield::applyDamage(float damage)
{
    //If shield block has any energy left
    if (shieldEnergy >= 0.0f) {
        //Subtract the damage from the health
        shieldEnergy -= damage;
    }

    //If the shield block has no energy...
    if (shieldEnergy <= 0.0f) {
        isShieldUp = false; //Kill it.
    }
}

//Apply damage to the shield as a whole
void applyDamageMaster(float damge)
{

}
