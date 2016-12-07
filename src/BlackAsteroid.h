#ifndef BLACKASTEROID_H
#define BLACKASTEROID_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "BaseEnemy.h"

/*
    Our black asteroid! The hardest enemy!
    This enemy will make your life miserable because...
    -It completely ignores the shield
    -It completely ignores the laser
    -It takes a great deal of shots to kill
    -It will only spawn directly above the player!
    -It is hard to see!
    -It moves the fastest!
    -IT CAUSES INSTANT DEATH!!!

    Saving grace?
    -Will only spawn one enemy, once per round
    -The spawn point doesnt change (dead center above player
    -Random spawn height (may take longer to reach player)
*/

class BlackAsteroid : public BaseEnemy
{
    public:
        //Automatic textures and variables
        BlackAsteroid();

        //Velocity - faster than the brown asteroid!
        const float enemyVelocity = 9.0f;

        //Are we spawned?
        bool isEnemySpawned = false;

        //Lots of health!
        const float maxHealth = 160;

        //Spawn our enemy
        void spawnEnemy(std::vector<BlackAsteroid*> tempEnemyVector);

        //Damage this enemy
        void applyDamage(float damage);

        //Grab the max enemies
        int getMaxEnemies() { return maxEnemies; }

    private:
        //This enemy is so mighty, only one may exist at a time...
        const int maxEnemies = 1;
};

#endif // BLACKASTEROID_H
