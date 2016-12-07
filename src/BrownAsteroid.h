#ifndef BROWNASTEROID_H
#define BROWNASTEROID_H

#include "BaseEnemy.h"
#include <SFML/Graphics.hpp>

/*
    Brown asteroid. Our medium enemy. This enemy...
    -Does NOT count towards a win
    -Does roughly two times shield damage
    -Moves slightly faster than white asteroid
    -Requires slightly more shots to kill
    -Evaporates to the laser. The laser will destroy this very, very quick.
    -Not too terribly common. About 1/4th as common as white asteroid
    -Can spawn anywhere on the X axis. Is not tied to the white asteroid wave
*/

class BrownAsteroid : public BaseEnemy
{
    public:
        //Automatic textures and variables
        BrownAsteroid();

        //Our constant move speed
        const float enemyVelocity = 7.5f;

        //Initial health value
        const float maxHealth = 80.0f;

        //Did we spawn an enemy?
        bool isEnemySpawned = false;

        //Damage our enemy
        void applyDamage(float damage);

        //Spawn our enemy at a random position
        void spawnRandomEnemy(std::vector<BrownAsteroid*> tempEnemyVector);

        //Get the maximum number of enemies
        int getMaxEnemies() { return maxEnemies; }

    private:
        //A max of 25 enemies of this type
        //are permitted at any given time.
        //For testings sake, only 1 enemy is permitted.
        const int maxEnemies = 1;


};

#endif // BROWNASTEROID_H
