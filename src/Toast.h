#ifndef TOAST_H
#define TOAST_H

#include "BaseEnemy.h"
#include <SFML/Graphics.hpp>

/*
    Our toast! - The medium enemy. This enemy...
    -Does NOT count towards a win. Instead, if this gets
        past you, you will lose ALL of your coffee filter.
            The toast really doesn't filter through well...
    -Does roughly two times coffee filter damage
    -Moves slightly faster than the egg
    -Requires slightly more cheerios/shots to kill
    -Evaporates to the paper towel. This destroys the toast very, very quick.
    -Not too terribly common. Enough to cause problems
    -Can spawn anywhere on the X axis. Is not tied to the egg wave
*/

class Toast : public BaseEnemy
{
    public:
        //Automatic textures and variables
        Toast();

        //Our constant move speed
        const float enemyVelocity = 7.5f;

        //Initial/max health value
        const float maxHealth = 80.0f;

        //Did we spawn an enemy?
        bool isEnemySpawned = false;

        //Damage our enemy
        void applyDamage(float damage);

        //Spawn our enemy at a random position
        void spawnRandomEnemy(std::vector<Toast*> tempEnemyVector);

        //Get the maximum number of enemies
        int getMaxEnemies() { return maxEnemies; }

    private:
        //A max of 5 enemies of this type
        //are permitted at any given time.
        const int maxEnemies = 5;


};

#endif // TOAST_H
