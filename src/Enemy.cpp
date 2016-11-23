#include <SFML/Graphics.hpp>
#include "include/Enemy.h"
#include <iostream>

Enemy::Enemy()
{
    if (!easyAsteroidTexture.loadFromFile("../textures/easyAsteroid.png")) {
        std::cout << "Error: Missing enemy texture";
    }
    easyAsteroid.setTexture(easyAsteroidTexture);

    if (!mediumAsteroidTexture.loadFromFile("../textures/mediumAsteroid.png")) {
        std::cout << "Error: Missing enemy texture";
    }
    mediumAsteroid.setTexture(mediumAsteroidTexture);
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

bool Enemy::checkForWin(std::vector<Enemy*> tempEnemyVector, int enemyCount)
{
    //Check for a win, where a win is defined as:
    //1) The enemy is not in play (dead)
    //2) There are no more living enemies remaining
    //      (did we kill ALL the enemies?)
    //3) The enemy was once in play, otherwise all idle enemies
    //      would be falsely counted

    //How many enemies are living?
    static int numberOfLiveEnemies = enemyCount;
    //For all possible enemies in play...
    for (int i = 0; i < maxEnemies; ++i) {
        //If the enemy is spawned...
        if (tempEnemyVector[i]->isSpawned) {
            //If the enemy is dead and not counted...
            if (tempEnemyVector[i]->isDead && !tempEnemyVector[i]->isCounted) {
                //Update the counter
                numberOfLiveEnemies -= 1;
                //Count the enemy only once
                tempEnemyVector[i]->isCounted = true;
            }
            if (numberOfLiveEnemies <= 0) {
                //Reset numberOfLiveEnemies.
                //If we are at the maximum amount of enemies,
                //do not add any further waves. Otherwise,
                //add an offset of 9 to the counter to
                //counter an otherwise impossible bug to fix
                // (adding 9 fixes it). This lets us win correctly.
                //MANUALLY LOOPING THROUGH THE WAVES IS UNSUPPORTED
                //AT THIS TIME...
                if (enemyCount == maxEnemies) {
                    numberOfLiveEnemies = enemyCount;
                } else {
                    numberOfLiveEnemies = enemyCount + 9;
                }

                for (int j = 0; j < maxEnemies; ++j) {
                    //No longer counted
                    tempEnemyVector[j]->isCounted = false;
                    //No longer spawned
                    tempEnemyVector[j]->isSpawned = false;
                }
                //We won, return true
                return true;
            }
        }
    }
    //We did not win, for any reason. Return false
    return false;
}

//Reset the asteroids positions, WIP wave-based system
void Enemy::resetEnemy(std::vector<Enemy*> tempEnemyVector)
{
    //Position our enemies on the X axis
    for (int i = 0; i < localEnemyCount; ++i) {
        static int counter = 0;
        if (counter == 9) {
            counter = 0;
        }
        tempEnemyVector[i]->positionX = counter * 90;
        counter += 1;
    }

    //Setup the y values properly
    for (int i = 0; i < localEnemyCount; ++i) {
        static int ammountToMove = 0;
        if (i == 0) {
            ammountToMove = 0;
        }
        if (i == 9) {
            ammountToMove = -100;
        }
        if (i == 18) {
            ammountToMove = -200;
        }
        if (i == 27) {
            ammountToMove = -300;
        }
        if (i == 36) {
            ammountToMove = -400;
        }
        if (i == 45) {
            ammountToMove = -500;
        }
        if (i == 54) {
            ammountToMove = -600;
        }
        if (i == 63) {
            ammountToMove = -700;
        }
        if (i == 72) {
            ammountToMove = -800;
        }
        tempEnemyVector[i]->positionY = ammountToMove;
        std::cout << "i = " << i << " Y = " << tempEnemyVector[i]->positionY << "\n";
    }
}

void Enemy::spawnEnemyWave(std::vector<Enemy*> tempEnemyVector, int waveNumber)
{
    //Count our waves and add enemies accordingly
    switch (waveNumber)
    {
    case 0:
        localEnemyCount = 0;
        std::cout << "Warning! waveNumber in function Enemy::spawnEnemyWave must be >= 1!\n";
        break;
    case 1:
        localEnemyCount = 9;
        break;
    case 2:
        localEnemyCount = 18;
        break;
    case 3:
        localEnemyCount = 27;
        break;
    case 4:
        localEnemyCount = 36;
        break;
    case 5:
        localEnemyCount = 45;
        break;
    case 6:
        localEnemyCount = 54;
        break;
    case 7:
        localEnemyCount = 63;
        break;
    case 8:
        //After the last wave, slowly increase
        //The speed of all enemies until the player
        //loses or gains the world record for waves
        //successfully completed.
        additionalEnemyVelocity += 1;
        localEnemyCount = maxEnemies;
        break;
    default:
        std::cout << "Error: Default case triggered in function Enemy::spawnEnemyWave...\n";
    }

    //Spawn our enemies
    for (int i = 0; i < localEnemyCount; ++i) {
        tempEnemyVector[i]->isDead = false;
        tempEnemyVector[i]->isSpawned = true;
    }

    //position them
    resetEnemy(tempEnemyVector);

    std::cout << "WAVE NUMBER: " << waveNumber << "\n";
}
