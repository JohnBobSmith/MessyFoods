#include "include/Mouse.h"
#include "include/Player.h"
#include <cmath>

//Unfortunately, this must be in the
//global namespace for this file.
//It is still heavily localized and thus
//it should not a problem.
Player player;


float Mouse::calculateMouseAngle(float mouseX, float mouseY, float positionX, float positionY)
{
    float angle = std::atan2(mouseY - positionY, mouseX - positionX);
    angle = angle * 180 / M_PI;
    if (angle < 0) {
        angle = 360 -(-angle);
    }
    return angle;
}

void Mouse::handleMouseEvents(sf::Event &event) {
    if (event.type == sf::Event::MouseMoved) {
        //Calculate the mouse position every frame
        mouseX = event.mouseMove.x;
        mouseY = event.mouseMove.y;
        //Set the angle relative to the player
        mouseAngle = calculateMouseAngle(mouseX, mouseY, (800 / 2),
                                        (600 - player.getHeight()));
    }
}
