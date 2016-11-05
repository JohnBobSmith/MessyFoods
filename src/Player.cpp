#include "include/Player.h"
#include <iostream>

Player::Player()
{
    if(!playerTexture.loadFromFile("../textures/moonbase.png")) {
        std::cout << "Error: Missing ../textures/moonbase.png!";
    }
    playerSprite.setTexture(playerTexture);

    //Set the position of the player to the bottom center of the screen
    playerSprite.setOrigin(playerTexture.getSize().x / 2, playerTexture.getSize().y / 2);
    playerSprite.setPosition(800 / 2, 600 - playerTexture.getSize().y / 2);

    //Set size, color, and position of our health bar
    healthBar.setSize(sf::Vector2f(20, 50));
    //Starts with full health
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setPosition(800 / 2 - 10, 600 - 75);
}
