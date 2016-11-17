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

        //Is an individual enemy spawned?
        bool isSpawned = false;

        //Is the enemy counted,
        //in regards to win checking?
        bool isCounted = false;

        //Did we spawn a wave of enemies?
        bool isWaveSpawned = false;

        //Constant movement speed
        const float enemyVelocity = 5.0f;

        //Constant max health of our enemies
        const float maxEnemyHealth = 40.0f;

        //How many enemies are playing/spawned
        //or should be spawn, those type of things.
        int localEnemyCount;

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

        //Expose the enemy max health for re-set purposes
        float getMaxEnemyHealth() { return maxEnemyHealth; }

        //Did we win?
        bool checkForWin(std::vector<Enemy*> tempEnemyVector, int enemyCount);

        //Spawn an enemy wave
        void spawnEnemyWave(std::vector<Enemy*> tempEnemyVector, int waveNumber);

        //Reset and respawn our enemies
        void resetEnemy(std::vector<Enemy*> tempEnemyVector);

    private:
        //The enemies texture
        sf::Texture enemyTexture;

        //For initializing, collision, and
        //drawing purposes only! Required
        //because said purposes require constant
        //values. Not intended to be changed.
        const int maxEnemies = 91;
};

#endif // ENEMY_H
