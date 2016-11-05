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

        //Did we spawn a wave of enemies?
        bool isWaveSpawned = false;

        //Constant movement speed
        const float enemyVelocity = 5.0f;

        //Constant max health of our enemies
        const float maxEnemyHealth = 40.0f;

        //The enemies modify-able health
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
        int getAdjustedMaxEnemies() { return enemiesInPlay; }

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
        //drawing purposes only! Required
        //because said purposes require constant
        //values. Not intended to be changed.
        const int maxEnemies = 91;

        //How many enemies to render, manipulate,
        //re-set or use? Default 9. Intended to
        //be changeable from our functions but
        //not by accident.
        int enemiesInPlay = 9;
};

#endif // ENEMY_H
