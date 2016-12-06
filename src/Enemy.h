#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "BaseEnemy.h"

class Enemy : public BaseEnemy
{
    public:
        //Setup our textures and
        //variables automatically
        Enemy();

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
        //for reaching the end of the game
        float additionalEnemyVelocity = 0.0f;

        //Constant max health of our enemies
        const float maxEnemyHealth = 40.0f;

        //Damage our objects based on N damage applied.
        void applyDamage(float damage);

        //Expose the max number of enemies,
        //for initialization, collision, drawing only!
        int getMaxEnemies() { return maxEnemies; }

        //Get the local amount of enemies
        int getLocalEnemyCount() { return localEnemyCount; }

        //Expose the enemy max health for re-set purposes
        float getMaxEnemyHealth() { return maxEnemyHealth; }

        //Did we win? Because this relates so heavily the the enemies,
        //it is present in the enemy class.
        bool checkForWin(std::vector<Enemy*> tempEnemyVector, int enemyCount);

        //Spawn an enemy wave
        void spawnEnemyWave(std::vector<Enemy*> tempEnemyVector, int waveNumber);

        //Reset and respawn our enemies
        void resetEnemy(std::vector<Enemy*> tempEnemyVector);

    private:
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
