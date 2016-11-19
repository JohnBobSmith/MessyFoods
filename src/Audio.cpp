#include "include/Audio.h"
#include <string>

Audio::Audio()
{
    bulletFireBuffer.loadFromFile("../audio/sfx/bulletFire.wav");
    bulletFire.setBuffer(bulletFireBuffer);

    shieldImpactBuffer.loadFromFile("../audio/sfx/shieldImpact.wav");
    shieldImpact.setBuffer(shieldImpactBuffer);

    laserFireBuffer.loadFromFile("../audio/sfx/laserFire.wav");
    laserFire.setBuffer(laserFireBuffer);

    enemyDeathBuffer.loadFromFile("../audio/sfx/enemyDeath.wav");
    enemyDeath.setBuffer(enemyDeathBuffer);

    mainMenuTheme.openFromFile("../audio/music/mainMenuTheme.wav");
}
