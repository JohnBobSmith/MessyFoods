#include <SFML/Graphics.hpp>
#include "include/Enemy.h"
#include <iostream>

Enemy::Enemy()
{
    if (!enemyTexture.loadFromFile("../textures/enemy.png")) {
        std::cout << "Error: Missing enemy texture";
    }
    enemySprite.setTexture(enemyTexture);
}

void Enemy::applyDamage(float damage)
{
    //If they have even a smidgen of health
    if (enemyHealth >= 0.0f) {
        //Subtract the damage from the health
        enemyHealth -= damage;
    }

    //If the enemy died...
    if (enemyHealth <= 0.0f) {
        isDead = true; //Kill it.
    }
}

bool Enemy::checkForWin(std::vector<Enemy*> tempEnemyVector)
{
    //If we win where a win is defined by
    //no more enemies in play
    static int counter = maxEnemies;
    for (int i = 0; i < maxEnemies; ++i) {
        if (tempEnemyVector[i]->isDead && !tempEnemyVector[i]->isCounted) {
            tempEnemyVector[i]->isCounted = true;
            counter -= 1;
        }
        if (counter <= 0) {
            for (int j = 0; j < maxEnemies; ++j) {
                tempEnemyVector[j]->isCounted = false;
            }
            counter = maxEnemies;
            return true;
        }
    }
    return false;
}
