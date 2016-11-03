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

        //The enemies base, modify-able health
        float enemyHealth = maxEnemyHealth;

        //Damage our objects based on N damage applied.
        void applyDamage(float damage);

        //Get the width and height of the enemy texture/sprite
        int getWidth() { return enemyTexture.getSize().x; }
        int getHeight() { return enemyTexture.getSize().y; }

        //Expose the max number of enemies,
        //for initialization, collision, drawing only!
        int getMaxEnemies() { return maxEnemies; }

        //Get a relative number of enemies, for more local stuff
        int getAdjustedMaxEnemies() { return enemiesInPlay;}

        //Expose our velocity
        float getVelocity() { return enemyVelocity; }

        //Expose the enemy max health for re-set purposes
        float getMaxEnemyHealth() { return maxEnemyHealth; }

        //Did we win?
        bool checkForWin(std::vector<Enemy*> tempEnemyVector);

        //Spawn an enemy wave
        void spawnEnemyWave(std::vector<Enemy*> tempEnemyVector, int waveNumber);

        //Reset and respawn our enemies
        void resetEnemy(std::vector<Enemy*> tempEnemyVector, int maximumEnemies);

    private:
        //The enemies texture
        sf::Texture enemyTexture;

        //For initializing, collision, and
        //drawing purposes only!
        const int maxEnemies = 90;

        //How many enemies are in play?
        //Default 9, intended to be changeable
        //from our functions.
        int enemiesInPlay = 9;

        //Constant movement speed
        const float enemyVelocity = 5.0f;

        //constant max health, used to
        //re-set the enemies to full health
        const float maxEnemyHealth = 50.0f;
};

#endif // ENEMY_H
