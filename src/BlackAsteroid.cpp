#include "BlackAsteroid.h"

BlackAsteroid::BlackAsteroid()
{
    //Set the texture. Inherited from BaseEnemy
    setTexture("../data/textures/blackasteroid.png");

    //The enemies modify-able health
    health = maxHealth;

    //Zero-init our velocity
    velocity.x = 0;
    velocity.y = 0;

    //Our enemy size
    size.x = texture.getSize().x;
    size.y = texture.getSize().y;
}

void BlackAsteroid::spawnEnemy()
{
    //TBD what goes here...
}

void BlackAsteroid::applyDamage(float damage)
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
