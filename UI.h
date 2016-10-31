#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>

class UI
{
    public:
        //Automatic textures
        UI();

        //Our start button
        sf::Sprite startButton;

        //Our help button
        sf::Sprite helpButton;

        //Our quit button
        sf::Sprite quitButton;

        //X and Y values for each button
        int startButtonX, startButtonY = 0;
        int helpButtonX, helpButtonY = 0;
        int quitButtonX, quitButtonY = 0;

        //Allow for us to pause/unpause the game,
        //For example, if the player dies, game over
        bool isPlaying = false;

        //If the player beat the game/level
        bool isWin = false;

    private:
        //Our textures
        sf::Texture startButtonTexture;
        sf::Texture helpButtonTexture;
        sf::Texture quitButtonTexture;

};

#endif // UI_H
