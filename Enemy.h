#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy
{
    public:
        //Setup our textures automatically
        Enemy();

        //The enemy sprite to draw on screen
        sf::Sprite enemySprite;

        //The enemies position and velocity
        float velocityX = 0;
        float velocityY = 0;
        float positionX = 0;
        float positionY = 0;

        //Is the enemy alive?
        bool isDead = true;

        //Is the enemy counted?
        //Used to assist with win checking,
        //where a win is defined as no more
        //enemies on screen.
        bool isCounted = false;

        //constant max health, used to
        //re-set the enemies to full health
        const float maxEnemyHealth = 50.0f;

        //The enemies base, modify-able health
        float enemyHealth = maxEnemyHealth;

        //Damage our objects based on N damage applied.
        void applyDamage(float damage);

        //Get the width and height of the enemy texture/sprite
        int getWidth() { return enemyTexture.getSize().x; }
        int getHeight() { return enemyTexture.getSize().y; }

        //Expose the max number of enemies
        int getMaxEnemies() { return maxEnemies; }

    private:
        //The enemies texture
        sf::Texture enemyTexture;

        //How many we have on screen
        const int maxEnemies = 90;

        //Constant movement speed
        const float enemyVelocity = 40.0f;
};

#endif // ENEMY_H
