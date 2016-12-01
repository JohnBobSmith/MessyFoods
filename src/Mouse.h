#ifndef MOUSE_H
#define MOUSE_H

#include <SFML/Graphics.hpp>

//Mouse functions and events
//Grabbing mouse position and what not
class Mouse
{
    public:
        //Calculate the angle of the mouse relative to a position
        float calculateMouseAngle(float mouseX, float mouseY, float positionX, float positionY);

        //Handle mouse events
        void handleMouseEvents(sf::Event &event);

        //Return the mouse angle
        float getMouseAngle() { return mouseAngle; }

        //Return the mouse positions
        float getMouseX() { return mouseX; }
        float getMouseY() { return mouseY; }

        //Return the mouse size
        int getWidth() { return mouseWidth; }
        int getHeight() { return mouseHeight; }

    private:
        //Our mouse X and Y values
        float mouseX;
        float mouseY;

        //Our mouse angle relative to a position
        float mouseAngle = 0.0f;

        //Give the mouse a width and height of 5
        //for the purpose of collision with our UI buttons
        int mouseWidth = 5;
        int mouseHeight = 5;

};

#endif // MOUSE_H
