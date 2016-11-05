#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player
{
    public:
        //Initialize player texture
        Player();

        //The player's sprite
        sf::Sprite playerSprite;

        //Our health bar rectangle
        sf::RectangleShape healthBar;

        //Our players constant max health,
        //used to re-set the game
        const float playerMaxHealth = 100.0f;

        //Our modify-able player health
        float playerHealth = playerMaxHealth;

        //Get the width/height of the player
        int getWidth() { return playerTexture.getSize().x; }
        int getHeight() { return playerTexture.getSize().y; }

    private:
        //Texture
        sf::Texture playerTexture;
};

#endif // PLAYER_H
