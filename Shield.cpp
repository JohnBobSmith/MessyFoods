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
