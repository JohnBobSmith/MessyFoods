#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include "Bullet.h"
#include "Enemy.h"
#include "CollisionBox.h"

//Allow the the use of pi
constexpr double pi_value() { return M_PI; }
double pi = pi_value();

//Are we in "debug" mode:
bool IS_DEBUG = false;

//Calculate a quadratic equation
sf::Vector2f calculateQuadratic(float n)
{
    sf::Vector2f tempVector;
    float y = 350 + (2.5 * (std::pow(n, 2)) / 800);
    float x = 390 + n;
    tempVector.x = x;
    tempVector.y = y;
    return tempVector;
}

//Calculate the mouse angle, in degrees
float calculateMouseAngle(float mouseX, float mouseY, float positionX, float positionY)
{
    float angle = std::atan2(mouseY - positionY, mouseX - positionX);
    angle = angle * (180/pi);

    if (angle < 0)
    {
        angle = 360 -(-angle);
    }

    return angle;
}

int main()
{
    //Our window and event union
    const int SCREEN_HEIGHT = 600;
    const int SCREEN_WIDTH = 800;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Spacey Rocks");
    sf::Event event;

    //Our background image
    sf::Sprite background;
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("textures/bg.png");
    background.setTexture(backgroundTexture);

    //Our stationary player
    sf::Sprite player;
    sf::Texture playerTexture;
    playerTexture.loadFromFile("textures/moonbase.png");
    player.setTexture(playerTexture);
    //Move the  to the bottom middle of the screen
    player.setOrigin(playerTexture.getSize().x / 2, playerTexture.getSize().y / 2);
    player.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - playerTexture.getSize().y / 2);

    //Our laser sprite
    sf::Sprite laser;
    sf::Texture laserTexture;
    laserTexture.loadFromFile("textures/laser.png");
    laser.setTexture(laserTexture);
    //Position the laser at the bottom, because it shoots
    //from the sides of our moon hut
    laser.setPosition(0, SCREEN_HEIGHT - 50);
    //a boolean value to determine when the lasers is in use or not
    bool isLaserOn = false;

    //Our shield
    //Enabled with right click, off otherwise
    sf::RectangleShape shieldSprite;
    shieldSprite.setFillColor(sf::Color::Cyan);
    shieldSprite.setSize(sf::Vector2f(20, 20));
    //shieldSprite.setRadius(25);
    //Max number of shield blocks to have
    const int maxShieldBlocks = 26;
    //determine if shield is in use or not
    bool isShieldActive = false;

    //Store our shield sprites in an std::vector for
    //easier collision detection
    std::vector<sf::RectangleShape> shieldVector;
    for (int i = 0; i < maxShieldBlocks; ++i) {
        shieldVector.push_back(shieldSprite);
    }

    //Our bullet object, and Bullet pointers
    //Store our bullets in the vector
    Bullet bullet;
    std::vector<Bullet*> bulletVector;
    //WE MUST ALSO REMEMBER TO CLEAN THIS UP
    for (int i = 0; i < bullet.getMaxBullets(); ++i) {
        bulletVector.push_back(new Bullet());
        //Also set the initial positions to match the gun
        bulletVector[i]->positionX = SCREEN_WIDTH / 2;
        bulletVector[i]->positionY = SCREEN_HEIGHT - playerTexture.getSize().y;
    }

    //SAME AS ABOVE BUT FOR OUR ENEMIES
    //REMEMBER TO CLEAN THIS UP
    Enemy enemy;
    std::vector<Enemy*> enemyVector;
    for (int i = 0; i < enemy.getMaxEnemies(); ++i) {
        enemyVector.push_back(new Enemy());
        //Enable the enemies
        enemyVector[i]->isDead = false;
    }

    //Position our enemies on the X axis
    for (int i = 0; i < enemy.getMaxEnemies(); ++i) {
        static int counterX = 0;
        enemyVector[i]->positionX = counterX * 105;
        counterX += 1;
        if (counterX == 8) {
            counterX = 0;
            //Reset the width
        }
    }

    //Setup the y values properly
    for (int i = 8; i < enemy.getMaxEnemies(); ++i) {
        static int ammountToMove = -100;
        enemyVector[i]->positionY = ammountToMove;
        if (i == (8 * 2)) {
            ammountToMove = -200;
        }
        if (i == (8 * 3)) {
            ammountToMove = -300;
        }
        if (i == (8 * 4)) {
            ammountToMove = -400;
        }
        if (i == (8 * 5)) {
            ammountToMove = -500;
        }
        if (i == (8 * 6)) {
            ammountToMove = -600;
        }
        if (i == (8 * 7)) {
            ammountToMove = -700;
        }
        if (i == (8 * 8)) {
            ammountToMove = -800;
        }
    }
    //Our collision detection object
    CollisionBox collisionbox;

    //Our mouse angle used in calculating
    //bullet trajectories
    float mouseAngle = 0.0f;

    //Frame rate limiter
    const float timeStep = 1/60.0f;

    /* * * * MAIN LOOP * * * */
    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            //If we release the spacebar
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Space) {
                    //Turn off the laser
                    isLaserOn = false;
                }
            }

            //If we release right mouse, turn off shield
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    isShieldActive = false;
                }
            }
        } //End event loop

       //Calculate the mouse angle each frame
        if (event.type == sf::Event::MouseMoved) {
            float mouseX = event.mouseMove.x;
            float mouseY = event.mouseMove.y;
            mouseAngle = calculateMouseAngle(mouseX, mouseY,
                    player.getPosition().x, player.getPosition().y);
        }

        //Mouse down event
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            //Shoot only one bullet at a time with mouse down
            static float delay = 0.5f;
            delay -= 0.01f;
            //Current bullet being shot.
            //Used to shoot exactly one bullet at a time.
            static int currentBullet = 0;

            if (delay <= 0.0f) { //The delay is done, so...
                //Fire our bullets one at a time
                currentBullet += 1;
                //If we run out of bullets, re-set to prevent a crash
                if (currentBullet >= bullet.getMaxBullets()) {
                    currentBullet = 0;
                }
                //Allow for our bullet to be rendered, and set the trajectory
                //According to where the mouse was clicked.
                bulletVector[currentBullet]->isActive = true;
                bulletVector[currentBullet]->velocityX = bullet.getConstantVelocity() * (cos(mouseAngle * pi / 180));
                bulletVector[currentBullet]->velocityY = bullet.getConstantVelocity() * (sin(mouseAngle * pi / 180));

                //Re-set the delay
                delay = 0.5;
            }
        }

        //Mouse right event
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            //Shields up!
            isShieldActive = true;
        }

        //Hold the keyboard to enable the laser
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            isLaserOn = true;
        }

        //Clear and draw the background
        window.clear(sf::Color::Black);
        window.draw(background);

        //Draw our debug squares
        if (IS_DEBUG) {
            sf::RectangleShape square;
            square.setFillColor(sf::Color::Yellow);
            square.setSize(sf::Vector2f(50, 50));
            sf::Vector2f squarePath;
            for (float i = -800.0f; i <= 800.0f; i += 20.0f) {
                squarePath.x = calculateQuadratic(i).x;
                squarePath.y = calculateQuadratic(i).y;
                square.setPosition(squarePath.x, squarePath.y);
                //Draw our debug square
                window.draw(square);
            }
        }

        //Draw the enemies
        for (int i = 0; i < enemy.getMaxEnemies(); ++i) {
            if (!enemyVector[i]->isDead) { //The enemy is NOT dead...
                enemyVector[i]->velocityY = 5.0; //Gravity on the Y axis
                enemyVector[i]->positionX += enemyVector[i]->velocityX * timeStep;
                enemyVector[i]->positionY += enemyVector[i]->velocityY * timeStep;
                enemyVector[i]->enemySprite.setPosition(enemyVector[i]->positionX, enemyVector[i]->positionY);
                window.draw(enemyVector[i]->enemySprite);
            }
        }

        //Draw the bullets
        for (int i = 0; i < bullet.getMaxBullets(); ++i) {
            if (bulletVector[i]->isActive) { //Live bullet, so move it
                bulletVector[i]->positionX += bulletVector[i]->velocityX * timeStep;
                bulletVector[i]->positionY += bulletVector[i]->velocityY * timeStep;
                bulletVector[i]->bulletSprite.setPosition(bulletVector[i]->positionX, bulletVector[i]->positionY);
                window.draw(bulletVector[i]->bulletSprite);
            }
        }

        //Draw our laser
        if (isLaserOn) {
            window.draw(laser);
        }

        //Draw our shield
        if (isShieldActive) {
            for (int i = 0; i < maxShieldBlocks; ++i) {
                window.draw(shieldVector[i]);
            }
        }

        //Check collision of enemies against laser
        if (isLaserOn) {
            for (int i = 0; i < enemy.getMaxEnemies(); ++i) {
                if (collisionbox.checkAABBcollision(laser.getPosition().x, laser.getPosition().y,
                                                laserTexture.getSize().x, laserTexture.getSize().y,
                                                enemyVector[i]->positionX, enemyVector[i]->positionY,
                                                enemy.getWidth(), enemy.getHeight())) {

                    //Kill the enemy
                    enemyVector[i]->isDead = true;
                }
            }
        }

        //Did any of our bullets collide with the enemies?
        //If so, damage the enemy and remove the bullet
        for (int i = 0; i < bullet.getMaxBullets(); ++i) {
            for (int j = 0; j < enemy.getMaxEnemies(); ++j) {
                //Ensure our bullet is actually capable of damaging our objects
                //before doing collision detection.
                if (bulletVector[i]->isActive && !enemyVector[j]->isDead) {
                    if (collisionbox.checkAABBcollision(bulletVector[i]->positionX, bulletVector[i]->positionY,
                                                        bullet.getWidth(), bullet.getHeight(),
                                                        enemyVector[j]->positionX, enemyVector[j]->positionY,
                                                        enemy.getWidth(), enemy.getHeight())) {
                        //Collision detected!
                        bulletVector[i]->isActive = false; //No longer rendered
                        enemyVector[j]->applyDamage(bullet.bulletDamage);
                    }
                }
            }
        }

        //If a bullet misses and goes off screen, kill it too
        for (int i = 0; i < bullet.getMaxBullets(); ++i) {
            if (bulletVector[i]->positionX > SCREEN_WIDTH || bulletVector[i]->positionX < 0) {
                bulletVector[i]->isActive = false;
            }
            if (bulletVector[i]->positionY > SCREEN_HEIGHT || bulletVector[i]->positionY < 0) {
                bulletVector[i]->isActive = false;
            }
        }

        //If the bullets are dead...
        for (int i = 0; i < bullet.getMaxBullets(); ++i) {
            if (!bulletVector[i]->isActive) {
                //re-set their initial positions
                //so they can be used again
                bulletVector[i]->positionX = SCREEN_WIDTH / 2;
                bulletVector[i]->positionY = SCREEN_HEIGHT - playerTexture.getSize().y;
            }
        }

        //Draw our player
        window.draw(player);
        window.display();
    } //End game loop

    std::cout << "Cleaning up bullets... Done\n";
    for (std::vector<Bullet*>::iterator it = bulletVector.begin(); it != bulletVector.end(); it++){
        delete *it;
    }

    std::cout << "Cleaning up enemies... Done\n";
    for (std::vector<Enemy*>::iterator it = enemyVector.begin(); it != enemyVector.end(); it++){
        delete *it;
    }
} //End main
