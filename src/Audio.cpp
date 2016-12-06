#include "Audio.h"
#include <string>

Audio::Audio()
{
    bulletFireBuffer.loadFromFile("../data/sfx/bulletFire.wav");
    bulletFire.setBuffer(bulletFireBuffer);

    shieldImpactBuffer.loadFromFile("../data/sfx/shieldImpact.wav");
    shieldImpact.setBuffer(shieldImpactBuffer);

    laserFireBuffer.loadFromFile("../data/sfx/laserFire.wav");
    laserFire.setBuffer(laserFireBuffer);

    enemyDeathBuffer.loadFromFile("../data/sfx/enemyDeath.wav");
    enemyDeath.setBuffer(enemyDeathBuffer);

    mainMenuTheme.openFromFile("../data/music/mainMenuTheme.wav");
    mainMenuTheme.setLoop(true);
}
