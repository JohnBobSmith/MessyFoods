#ifndef BACON_H
#define BACON_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "BaseEnemy.h"

/*
    Our BACON!! Who doesn't love bacon right?
    This enemy will make your life deliciously miserable...
    -Bacon completely ignores the coffee filter
    -Bacon completely ignores the paper towel
    -Bacon takes a lot of cheerios to destroy
    -Bacon will only spawn directly above the player!
        -BACON IS COMING FOR YOU!!!
    -Contrary to popular belief, bacon moves fast!
    -BACON CAUSES INSTANT DEATH IF IT POLLUTES YOUR CEREAL BOWL!

    The good news is...
    -Bacon will only spawn once per round
    -Bacon will always spawn directly above the player
    -Random spawn height (may take longer to reach player)
*/

class Bacon : public BaseEnemy
{
    public:
        //Automatic textures and variables
        Bacon();

        //Velocity - faster than the brown asteroid!
        const float enemyVelocity = 9.0f;

        //Are we spawned?
        bool isEnemySpawned = false;

        //Lots of health!
        const float maxHealth = 160;

        //Spawn our enemy
        void spawnEnemy(std::vector<Bacon*> tempEnemyVector);

        //Damage this enemy
        void applyDamage(float damage);

        //Grab the max enemies
        int getMaxEnemies() { return maxEnemies; }

    private:
        //This enemy is so mighty, only one may exist at a time...
        const int maxEnemies = 1;
};

#endif // BLACKASTEROID_H
