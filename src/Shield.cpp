#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "Shield.h"
#include <iostream>

Shield::Shield()
{
    if (!shieldTexture.loadFromFile( PKGDATADIR "//textures/shield.png")) {
        std::cout << "Error, missing shield texture...\n";
    }
    shieldSprite.setTexture(shieldTexture);
}

void Shield::applyDamage(float damage)
{
    //If shield block has any energy left
    if (shieldEnergy >= 0.0f) {
        //Subtract the damage from the energy
        shieldEnergy -= damage;
    }

    //If the shield block has no energy...
    if (shieldEnergy <= 0.0f) {
        isChunkActive = false; //Kill it.
    }
}
