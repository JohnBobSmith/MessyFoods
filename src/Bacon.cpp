#include "Bacon.h"
#include "G_Miscfuncandvar.h"
#include <cmath>

Bacon::Bacon()
{
    //Set the texture. Inherited from BaseEnemy
    setTexture("../data/textures/bacon.png");

    //The enemies modify-able health
    health = maxHealth;

    //Zero-init our velocity
    velocity.x = 0;
    velocity.y = 0;

    //Our enemy size
    size.x = texture.getSize().x;
    size.y = texture.getSize().y;
}

void Bacon::spawnEnemy(std::vector<Bacon*> tempEnemyVector)
{
    //Screen width and RNG
    G_Miscfuncandvar gmiscfuncandvar;

    //Position directly above the player
    for (int i = 0; i < maxEnemies; ++i) {
        tempEnemyVector[i]->position.x = gmiscfuncandvar.screenWidth / 2 - size.x / 2;
        //Start at the top of the screen, randomly. fabsf is absolute float
        float randomNumber = -fabsf(gmiscfuncandvar.getRandomNumber() / 2);
        tempEnemyVector[i]->position.y = randomNumber;

        tempEnemyVector[i]->isActive = true;
    }

}

void Bacon::applyDamage(float damage)
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
