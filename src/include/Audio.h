#ifndef AUDIO_H
#define AUDIO_H

#include <SFML/Audio.hpp>
#include <string>

class Audio
{
    public:
        /*
            Sound names follow a very simple syntax so
            I will always know what goes where. The rule is:
              soundObject_stateThatSoundIsIn
            without the underscore. For example, you have a bullet.
            The bullet has to be fired, and hit something. These
            two sounds are now named: bulletFire, bulletImpact.
            For 2 impact sounds, bulletImpact01, bulletImpact02,
            etc. All binary audio files follow this convention.
        */
        //Initialize our sounds
        Audio();

        //Our sounds
        sf::Sound bulletFire;
        sf::Sound enemyDeath;
        sf::Sound shieldImpact;
        sf::Sound laserFire;

        //Our music
        sf::Music mainMenuTheme;

    private:
        //One buffer per sound
        sf::SoundBuffer bulletFireBuffer;
        sf::SoundBuffer enemyDeathBuffer;
        sf::SoundBuffer shieldImpactBuffer;
        sf::SoundBuffer laserFireBuffer;
};

#endif // AUDIO_H



