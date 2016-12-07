#ifndef WHITEASTEROID_H
#define WHITEASTEROID_H

#include <SFML/Graphics.hpp>
#include "BaseEnemy.h"

/*
    Our easiest enemy, the white asteroid.
    THIS IS THE ONLY ENEMY TYPE THAT COUNTS TOWARDS A WIN!
    This enemy is:
    -Very plentiful
    -Easy to kill
    -Does relatively low damage to the shields
    -Increases in numbers (wave based) as time goes by
*/

class WhiteAsteroid : public BaseEnemy
{
    public:
        //Setup our textures and
        //variables automatically
        WhiteAsteroid();

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
        bool checkForWin(std::vector<WhiteAsteroid*> tempEnemyVector, int enemyCount);

        //Spawn an enemy wave
        void spawnEnemyWave(std::vector<WhiteAsteroid*> tempEnemyVector, int waveNumber);

        //Reset and respawn our enemies
        void resetEnemy(std::vector<WhiteAsteroid*> tempEnemyVector);

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

#endif // WHITEASTEROID_H
