#include "Audio.h"
#include "Resources.h"
#include <string>

Audio::Audio()
{
    bulletFireBuffer.loadFromFile( PKGDATADIR "/sfx/bulletFire.wav");
    bulletFire.setBuffer(bulletFireBuffer);

    shieldImpactBuffer.loadFromFile( PKGDATADIR "/sfx/shieldImpact.wav");
    shieldImpact.setBuffer(shieldImpactBuffer);

    laserFireBuffer.loadFromFile( PKGDATADIR "/sfx/laserFire.wav");
    laserFire.setBuffer(laserFireBuffer);

    enemyDeathBuffer.loadFromFile( PKGDATADIR "/sfx/enemyDeath.wav");
    enemyDeath.setBuffer(enemyDeathBuffer);

    mainMenuTheme.openFromFile( PKGDATADIR "/music/mainMenuTheme.wav");
    mainMenuTheme.setLoop(true);
}
