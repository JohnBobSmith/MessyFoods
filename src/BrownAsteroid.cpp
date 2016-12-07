#include "BrownAsteroid.h"
#include "G_Miscfuncandvar.h"
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

BrownAsteroid::BrownAsteroid()
{
    //Set the texture. Inherited from BaseEnemy
    setTexture("../data/textures/brownasteroid.png");

    //The enemies modify-able health
    health = maxHealth;

    //Zero-init our velocity
    velocity.x = 0;
    velocity.y = 0;

    //Our enemy size
    size.x = texture.getSize().x;
    size.y = texture.getSize().y;
}

void BrownAsteroid::applyDamage(float damage)
{
    //If they have even a smidgen of health
    if (health >= 0.0f) {
        //Subtract the damage from the health
        health -= damage;
    }

    //If the enemy died...
    if (health <= 0.0f) {
        //Disable it
        isActive = false;
    }
}

void BrownAsteroid::spawnRandomEnemy(std::vector<BrownAsteroid*> tempEnemyVector)
{
    //Screen width
    G_Miscfuncandvar gmiscfuncandvar;

    //Our random number generator, more or less copy-pasted from
    //stackoverlow. See here (second answer):
    //http://stackoverflow.com/questions/7560114/random-number-c-in-some-range
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(80, gmiscfuncandvar.screenWidth - 80);

    for (int i = 0; i < maxEnemies; ++i) {
        //For the sake of testing, until this enemy
        //is fully implemented, the X value is fixed.
        tempEnemyVector[i]->position.x = distr(eng);
        //Start slightly above the top of the screen
        tempEnemyVector[i]->position.y = -(distr(eng) / 2);

        //Enable the enemy
        tempEnemyVector[i]->isActive = true;
    }
}
