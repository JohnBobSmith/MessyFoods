#ifndef BLACKASTEROID_H
#define BLACKASTEROID_H

#include <SFML/Graphics.hpp>
#include "BaseEnemy.h"

/*
    Our black asteroid! The hardest enemy!
    This enemy will make your life miserable because...
    -It completely ignores the shield
    -It completely ignores the laser
    -It takes a great deal of shots to kill
    -It will only spawn directly above the player!
    -It is hard to see!
    -IT CAUSES INSTANT DEATH!

    Saving grace?
    -This enemy moves slightly slower than the white asteroid
    -Will only spawn one enemy, once per round

*/

class BlackAsteroid : public BaseEnemy
{
    public:
        //Automatic textures and variables
        BlackAsteroid();

        //Velocity - slower than white asteroid
        const float enemyVelocity = 3.5f;

        //Are we spawned?
        bool isSpawned = false;

        //Lots of health!
        const float maxHealth = 160;

        //Spawn our enemy
        void spawnEnemy();

        //Damage this enemy
        void applyDamage(float damage);

        //Grab the max enemies
        int getMaxEnemies() { return maxEnemies; }

    private:
        //This enemy is so mighty, only one may exist at a time...
        const int maxEnemies = 1;
};

#endif // BLACKASTEROID_H
