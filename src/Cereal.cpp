#include <SFML/Graphics.hpp>
#include "Cereal.h"
#include "Resources.h"
#include <iostream>

Cereal::Cereal()
{
    if (!cerealTexture.loadFromFile( PKGDATADIR "/textures/cereal.png")) {
        std::cout << "Error, missing cereal texture...\n";
    }
    cerealSprite.setTexture(cerealTexture);
}
