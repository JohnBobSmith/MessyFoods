#include "BrownAsteroid.h"
#include "G_Miscfuncandvar.h"
#include <iostream>
#include <cmath>
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
    //Screen width and RNG
    G_Miscfuncandvar gmiscfuncandvar;

    for (int i = 0; i < maxEnemies; ++i) {
        //Random X positions. fabsf is absolute floating point
        float randomNumberX = fabsf(gmiscfuncandvar.getRandomNumber());
        tempEnemyVector[i]->position.x = randomNumberX;

        //Start slightly above the top of the screen. fabsf is absolute floating point
        float randomNumberY = -fabsf(gmiscfuncandvar.getRandomNumber()) / 2;
        tempEnemyVector[i]->position.y = randomNumberY;

        //Enable the enemy
        tempEnemyVector[i]->isActive = true;
    }
}
