#include <SFML/Graphics.hpp>
#include "include/Bullet.h"
#include <iostream>

Bullet::Bullet()
{
    if (!bulletTexture.loadFromFile("../textures/bullet.png")) {
        std::cout << "Error, missing bullet texture...\n";
    }
    bulletSprite.setTexture(bulletTexture);
}
