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

//Reset the asteroids positions, WIP wave-based system
void Enemy::resetEnemy(std::vector<Enemy*> tempEnemyVector, int maximumEnemies)
{
    //Kill all enemies
    for (int i = 9; i < maxEnemies; ++i) {
        tempEnemyVector[i]->isDead = true;
    }

    //Position our enemies on the X axis
    int counterX = 0;
    for (int i = 0; i < maxEnemies; ++i) {
        if (counterX == 9) {
            counterX = 0;
            //Reset the width
        }
        tempEnemyVector[i]->positionX = counterX * 90;
        counterX += 1;
    }

    //Setup the y values properly
    for (int i = 0; i < maxEnemies; ++i) {
        static int ammountToMove = 0;
        tempEnemyVector[i]->positionY = ammountToMove;
        if (i == (9)) {
            ammountToMove = -100;
        }
        if (i == (18)) {
            ammountToMove = -200;
        }
        if (i == (27)) {
            ammountToMove = -300;
        }
        if (i == (36)) {
            ammountToMove = -400;
        }
        if (i == (45)) {
            ammountToMove = -500;
        }
        if (i == (54)) {
            ammountToMove = -600;
        }
        if (i == (63)) {
            ammountToMove = -700;
        }
        if (i == (72)) {
            ammountToMove = -800;
        }
        if (i == (81)) {
            ammountToMove = -900;
        }
        if (i == (90)) {
            ammountToMove = -1000;
        }
    }
}

void Enemy::spawnEnemyWave(std::vector<Enemy*> tempEnemyVector, int waveNumber)
{
    static int newWaveNumber;
    if (waveNumber <= 0) { //Error
        newWaveNumber = 0;
        std::cout << "Invalid entry for argument waveNumber in function spawnEnemyWave...\n";
    }

    if (waveNumber == 1) {
        newWaveNumber = 9;
    }

    if (waveNumber == 2) {
        newWaveNumber = 19;
    }

    //Spawn newWaveNumber worth of enemies
    for (int i = 0; i < newWaveNumber; ++i) {
        tempEnemyVector[i]->isDead = false;
    }
    //position them
    resetEnemy(tempEnemyVector, maxEnemies);
}
