#include "BaseEnemy.h"
#include <string>
#include <iostream>

//Every enemy must have some default values
BaseEnemy::BaseEnemy()
{
    //The enemy is disabled until
    //explicitly turned on elsewhere
    isActive = false;

    //position is initialized to zero, to
    //prevent junk values later on
    position.x = 0;
    position.y = 0;

    //Likewise for size
    size.x = 0;
    size.y = 0;

    //Enemies are assumed to start with 100 health
    health = 100.0f;
}

bool BaseEnemy::setTexture(std::string path)
{
    //Load and set the texture
    if (!texture.loadFromFile(path.c_str())) {
        std::cerr << "Error: Missing texture " << path.c_str();
        return false;
    }
    sprite.setTexture(texture);
    return true;
}
