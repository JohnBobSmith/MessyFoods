#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <iostream>

Bullet::Bullet()
{
    if (!bulletTexture.loadFromFile("../data/textures/bullet.png")) {
        std::cout << "Error, missing bullet texture...\n";
    }
    bulletSprite.setTexture(bulletTexture);
}
