#include "Text.h"
#include "G_Miscfuncandvar.h"

Text::Text()
{
    //Screen dimensions
    G_Miscfuncandvar gmiscfuncandvar;

    //Load our font
    blockFont.loadFromFile("../data/fonts/ehsmb.ttf");

    //Load our game over text
    gameOverText.setFont(blockFont);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(110);
    gameOverText.setColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Regular);
    //Center the text on screen
    gameOverText.setPosition(gmiscfuncandvar.screenWidth / 8, gmiscfuncandvar.screenHeight / 3);

    //Load our victory/win text
    winText.setFont(blockFont);
    winText.setString("You WIN!!");
    winText.setCharacterSize(110);
    winText.setColor(sf::Color::Green);
    winText.setStyle(sf::Text::Regular);
    //Center the text on screen
    winText.setPosition(gmiscfuncandvar.screenWidth / 8, gmiscfuncandvar.screenHeight / 3);

    //Load our "Space bar to start" text
    spaceTostartText.setFont(blockFont);
    spaceTostartText.setString("Space bar to start");
    spaceTostartText.setCharacterSize(55);
    spaceTostartText.setColor(sf::Color::Yellow);
    spaceTostartText.setStyle(sf::Text::Regular);
    //Position this text just below our win/loss text
    spaceTostartText.setPosition(gmiscfuncandvar.screenWidth / 8, gmiscfuncandvar.screenHeight / 2);
}




