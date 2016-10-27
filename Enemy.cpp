#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <iostream>

Enemy::Enemy()
{
    if (!enemyTexture.loadFromFile("textures/enemy.png")) {
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

