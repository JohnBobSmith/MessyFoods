#include <SFML/Graphics.hpp>
#include <iostream>
#include "UI.h"

UI::UI()
{
    //Load each texture
    if (!startButtonTexture.loadFromFile("textures/ui/start.png")) {
        std::cout << "Missing start button texture!\n";
    }
    startButton.setTexture(startButtonTexture);

    if (!quitButtonTexture.loadFromFile("textures/ui/quit.png")) {
        std::cout << "Missing quit button texture!\n";
    }
    quitButton.setTexture(quitButtonTexture);

    if (!helpButtonTexture.loadFromFile("textures/ui/help.png")) {
        std::cout << "Missing help button texture!\n";
    }
    helpButton.setTexture(helpButtonTexture);
}
