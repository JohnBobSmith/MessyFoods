#ifndef BASEENEMY_H
#define BASEENEMY_H

#include <SFML/Graphics.hpp>
#include <string>

/*
    Our base enemy class:
    This class contains things a GENERIC
    enemy MUST have. We are assuming
    that all enemies for the purpose of this
    program must also have a health.
*/

class BaseEnemy
//Every enemy must have...
{
    public:
        //Some default values
        BaseEnemy();

        //A sprite
        sf::Sprite sprite;

        //A texture
        sf::Texture texture;

        //An X and Y position
        sf::Vector2f position;

        //A velocity
        sf::Vector2f velocity;

        //A width and a height
        sf::Vector2f size;

        //Some health
        float health;

        //A way to determine if said
        //enemy is in use or not
        bool isActive;

        //And a way to set the texture
        bool setTexture(std::string path);
};

#endif // BASEENEMY_H
