#ifndef TEXT_H
#define TEXT_H

#include <SFML/Graphics.hpp>

class Text
{
    public:
        //Automatically initialize everything
        //because it's convenient
        Text();

        //Our game over text
        sf::Text gameOverText;

        //Our victory text
        sf::Text winText;

        //Our "Space to start" text
        sf::Text spaceTostartText;

    private:
        //Our square font.
        //Private to avoid accidental changing.
        sf::Font blockFont;
};

#endif // TEXT_H
