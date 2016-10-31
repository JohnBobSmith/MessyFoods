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
        int startButtonX = 300;
        int startButtonY = 75;
        int helpButtonX = 300;
        int helpButtonY = 250;
        int quitButtonX = 300;
        int quitButtonY = 450;

        //Allow for us to pause/unpause the game,
        //For example, if the player dies, game over
        bool isPlaying = false;

        //If the player beat the game/level,
        //otherwise known as a win
        bool isWin = false;

        //Are we in the main menu?
        //If so, display the various buttons.
        bool isMainMenu = true;

        //Get the height and width of
        //Our boxes. Assumes all boxes
        //are the same size as startButtonTexture.
        int getWidth() { return startButtonTexture.getSize().x; }
        int getHeight() { return startButtonTexture.getSize().y; }

    private:
        //Our textures
        sf::Texture startButtonTexture;
        sf::Texture helpButtonTexture;
        sf::Texture quitButtonTexture;

};

#endif // UI_H
