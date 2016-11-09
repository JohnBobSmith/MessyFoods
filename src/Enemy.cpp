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
            //Re-set all counter parameters
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
    //Position our enemies on the X axis
    static int counterX = 0;
    for (int i = 0; i < maximumEnemies; ++i) {
        if (counterX == 9) {
            counterX = 0;
            //Reset the width
        }
        tempEnemyVector[i]->positionX = counterX * 90;
        counterX += 1;
    }

    //Setup the y values properly
    for (int i = 0; i < maximumEnemies; ++i) {
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
    //Disable all enemies to start
    for (int i = 0; i < enemiesInPlay; ++i) {
        tempEnemyVector[i]->isDead = true;
    }

    //Count our waves and add enemies accordingly
    static int newWaveNumber;
    switch (waveNumber)
    {
    case 0:
        newWaveNumber = 0;
        std::cout << "Warning! waveNumber in function Enemy::spawnEnemyWave must be >= 1!\n";
        break;
    case 1:
        newWaveNumber = 9;
        break;
    case 2:
        newWaveNumber = 18;
        break;
    case 3:
        newWaveNumber = 27;
        break;
    case 4:
        newWaveNumber = 36;
        break;
    case 5:
        newWaveNumber = 45;
        break;
    case 6:
        newWaveNumber = 54;
        break;
    case 7:
        newWaveNumber = 63;
        break;
    case 8:
        newWaveNumber = 72;
        break;
    default:
        //You won the game!
        //Loop maxEnemies worth of enemies.
        newWaveNumber = maxEnemies;
    }

    //Current amount of enemies in use
    enemiesInPlay = newWaveNumber;

    //Spawn enemiesInPlay worth of enemies
    for (int i = 0; i < enemiesInPlay; ++i) {
        tempEnemyVector[i]->isDead = false;
    }

    //position them
    resetEnemy(tempEnemyVector, enemiesInPlay);
}
