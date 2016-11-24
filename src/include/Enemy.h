#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy
{
    public:
        //Setup our textures automatically
        Enemy();

        //The enemy sprites to be drawn on screen
        sf::Sprite asteroid;

        //The enemies position and velocity
        float velocityX = 0;
        float velocityY = 0;
        float positionX = 0;
        float positionY = 0;

        //Is the enemy alive?
        bool isDead = true;

        //Is an individual enemy spawned?
        bool isSpawned = false;

        //Is the enemy counted,
        //in regards to win checking?
        bool isCounted = false;

        //Did we spawn a wave of enemies?
        bool isWaveSpawned = false;

        //Constant movement speed
        const float enemyVelocity = 5.0f;

        //Additional movement speed, added for
        //some reason IE reaching the end of the game
        float additionalEnemyVelocity = 0.0f;

        //Constant max health of our enemies
        const float maxEnemyHealth = 40.0f;

        //The enemies modify-able health
        float enemyHealth = maxEnemyHealth;

        //Damage our objects based on N damage applied.
        void applyDamage(float damage);

        //Get the width and height of the enemy texture
        //This assumes all enemies are the same size as
        //our asteroidTexture
        int getWidth() { return asteroidTexture.getSize().x; }
        int getHeight() { return asteroidTexture.getSize().y; }

        //Expose the max number of enemies,
        //for initialization, collision, drawing only!
        int getMaxEnemies() { return maxEnemies; }

        //Get the local amount of enemies
        int getLocalEnemyCount() { return localEnemyCount; }

        //Expose the enemy max health for re-set purposes
        float getMaxEnemyHealth() { return maxEnemyHealth; }

        //Did we win?
        bool checkForWin(std::vector<Enemy*> tempEnemyVector, int enemyCount);

        //Spawn an enemy wave
        void spawnEnemyWave(std::vector<Enemy*> tempEnemyVector, int waveNumber);

        //Reset and respawn our enemies
        void resetEnemy(std::vector<Enemy*> tempEnemyVector);

    private:
        //The enemy textures
        sf::Texture asteroidTexture;

        //For initializing, collision, and
        //drawing purposes only! Required
        //because said purposes require constant
        //values. Not intended to be changed.
        const int maxEnemies = 72;

        //How many enemies are playing/spawned
        //or should be spawn, those type of things.
        int localEnemyCount = 9;
};

#endif // ENEMY_H
