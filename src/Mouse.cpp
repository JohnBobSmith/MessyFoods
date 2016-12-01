#include "Mouse.h"
#include "Player.h"
#include "G_Miscfuncandvar.h"
#include <cmath>

//Unfortunately, these must be in the
//global namespace for this file.
//It is still heavily localized and thus
//it should not a problem.
Player player;
G_Miscfuncandvar gmiscfuncandvar;


float Mouse::calculateMouseAngle(float mouseX, float mouseY, float positionX, float positionY)
{
    float angle = std::atan2(mouseY - positionY, mouseX - positionX);
    angle = angle * 180 / gmiscfuncandvar.pi;
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
        mouseAngle = calculateMouseAngle(mouseX, mouseY, (gmiscfuncandvar.screenWidth / 2),
                                        (gmiscfuncandvar.screenHeight - player.getHeight()));
    }
}
