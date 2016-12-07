#include <SFML/Graphics.hpp>
#include "Cereal.h"
#include <iostream>

Cereal::Cereal()
{
    if (!cerealTexture.loadFromFile("../data/textures/cereal.png")) {
        std::cout << "Error, missing cereal texture...\n";
    }
    cerealSprite.setTexture(cerealTexture);
}
