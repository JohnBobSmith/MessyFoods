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

        //Our help page
        sf::Sprite helpPage;

        //Our quit button
        sf::Sprite quitButton;

        //X and Y values for each button
        int startButtonX = 300;
        int startButtonY = 75;
        int helpButtonX = 300;
        int helpButtonY = 250;
        int helpPageX = 0;
        int helpPageY = 0;
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
        //Dont show our help unless in the correct
        //menu to do so
        bool isHelpDisplayed = false;

        //Get the height and width of
        //Our boxes. Assumes all boxes
        //are the same size as startButtonTexture.
        int getWidth() { return startButtonTexture.getSize().x; }
        int getHeight() { return startButtonTexture.getSize().y; }

        //Width and height of our help page because
        //this sprite here is significantly larger
        int getHelpPageWidth() { return helpPageTexture.getSize().x; }
        int getHelpPageHeight() { return helpPageTexture.getSize().y; }

    private:
        //Our textures
        sf::Texture startButtonTexture;
        sf::Texture helpButtonTexture;
        sf::Texture helpPageTexture;
        sf::Texture quitButtonTexture;

};

#endif // UI_H
