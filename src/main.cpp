#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "Player.h"
#include "Bullet.h"
#include "WhiteAsteroid.h"
#include "Shield.h"
#include "CollisionBox.h"
#include "UI.h"
#include "Audio.h"
#include "Laser.h"
#include "Mouse.h"
#include "G_Miscfuncandvar.h"
#include "Text.h"

int main()
{
    //Initialize or global functions and variables
    //This must be done immediately
    G_Miscfuncandvar gmiscfuncandvar;

    //Frame rate limiter
    const float timeStep = 1/60.0f;

    //Our window and event union
    sf::RenderWindow window(sf::VideoMode(gmiscfuncandvar.screenWidth, gmiscfuncandvar.screenHeight), "Spacey Rocks");
    sf::Event event;

    //Our background image
    sf::Sprite background;
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../data/textures/background.png");
    background.setTexture(backgroundTexture);

    //Our texts
    Text text;

    //Our mouse
    Mouse mouse;

    //The laser
    Laser laser;

    //Our collision detection object
    CollisionBox collisionbox;

    //Our user interface object
    UI ui;

    //The player
    Player player;

    //Audio
    Audio audio;
    //Play music immediately
    audio.mainMenuTheme.play();

    //Store our bullets in an std::vector
    //WE MUST REMEMBER TO CLEAN UP ANYTHING
    //CREATED WITH NEW...
    Bullet bullet;
    std::vector<Bullet*> bulletVector;
    for (int i = 0; i < bullet.getMaxBullets(); ++i) {
        bulletVector.push_back(new Bullet());
        //Set the initial positions to match the gun
        bulletVector[i]->positionX = gmiscfuncandvar.screenWidth/ 2;
        bulletVector[i]->positionY = gmiscfuncandvar.screenHeight - player.getHeight();
    }

    //White asteroid/easiest enemy object and pointers
    WhiteAsteroid whiteasteroid;
    std::vector<WhiteAsteroid*> whiteAsteroidVector;
    for (int i = 0; i < whiteasteroid.getMaxEnemies(); ++i) {
        whiteAsteroidVector.push_back(new WhiteAsteroid());
    }

    //Shield object and pointers
    Shield shield;
    std::vector<Shield*> shieldVector;
    for (int i = 0; i < shield.getMaxShieldBlocks(); ++i) {
        shieldVector.push_back(new Shield());
        //Enable the shield
        shieldVector[i]->isChunkActive= true;
    }

    //Position the shield blocks
    static int counter = 0;
    for (float i = -300; i <= 300; i += 10) {
        float x = gmiscfuncandvar.calculateQuadratic(i).x;
        float y = gmiscfuncandvar.calculateQuadratic(i).y;
        shieldVector[counter]->positionX = x;
        shieldVector[counter]->positionY = y;
        shieldVector[counter]->shieldSprite.setPosition(shieldVector[counter]->positionX,
                                                        shieldVector[counter]->positionY);
        //Do not overflow, because that would crash our game
        if (counter == shield.getMaxShieldBlocks() - 1) {
            break;
        }
        counter += 1;
    }

    /* * * * MAIN LOOP * * * */
    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                //We pressed the titlebar's X button
                window.close(); //Quit.
            }
            //Handle mouse events
            mouse.handleMouseEvents(event);

            //If we release right mouse, turn off laser
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    laser.isActive = false;
                }
            }
        } //End event loop

        //Return to the main menu at any time when we press escape.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            ui.isMainMenu = true;
        }

        //Process these events only if we are playing
        if (ui.isPlaying) {
            //Mouse down event. Shoot with left mouse
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                //Our rate of fire. Subtract 0.01f here always.
                //Do not change this value. Instead, adjust
                //bullet.maxRateOfFire to change fire rate
                bullet.rateOfFire -= 0.01f;

                //Current bullet being shot.
                //Used to shoot exactly one bullet at a time.
                static int currentBullet = 0;

                if (bullet.rateOfFire <= 0.0f) { //The our counter expired, so...
                    //Fire our bullets one at a time
                    currentBullet += 1;
                    //If we run out of bullets, re-set to prevent a crash
                    if (currentBullet >= bullet.getMaxBullets()) {
                        currentBullet = 0;
                    }
                    //Allow for our bullet to be rendered, and set the trajectory
                    //According to where the mouse was clicked.
                    bulletVector[currentBullet]->isActive = true;
                    bulletVector[currentBullet]->velocityX = bullet.bulletVelocity *
                            (cos(mouse.getMouseAngle() * gmiscfuncandvar.pi / 180));
                    bulletVector[currentBullet]->velocityY = bullet.bulletVelocity *
                            (sin(mouse.getMouseAngle() * gmiscfuncandvar.pi / 180));

                    //Play our firing sound
                    audio.bulletFire.play();

                    //Re-set the counter
                    bullet.rateOfFire = bullet.maxRateOfFire;
                }
            }

            //Mouse right event. Fire our laser.
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                laser.isActive = true;
            }
        }

        //END OF EVENTS, START OF GAME LOGIC

        //Handle our music here as this seems
        //to be the only place it works...
        //If we are not in the main menu, mute music
        if (!ui.isMainMenu) {
            audio.mainMenuTheme.setVolume(50);
        } else {
            audio.mainMenuTheme.setVolume(75);
        }

        //Running our actual game
        if (ui.isPlaying) {
            //Enemy wave spawning logic
            if (!whiteasteroid.isWaveSpawned) {
                //Spawn 1 wave at a time
                static int counter = 1;
                //Because our counter variable is not
                //A constant expression, we must use
                //if statements instead of case, or
                //we get a compiler error.
                if (counter == 1 && !whiteasteroid.isWaveSpawned) {
                    whiteasteroid.spawnEnemyWave(whiteAsteroidVector, 1);
                    counter += 1;
                    whiteasteroid.isWaveSpawned = true;
                }
                if (counter == 2 && !whiteasteroid.isWaveSpawned) {
                    whiteasteroid.spawnEnemyWave(whiteAsteroidVector, 2);
                    counter += 1;
                    whiteasteroid.isWaveSpawned = true;
                }
                if (counter == 3 && !whiteasteroid.isWaveSpawned) {
                    whiteasteroid.spawnEnemyWave(whiteAsteroidVector, 3);
                    counter += 1;
                    whiteasteroid.isWaveSpawned = true;
                }
                if (counter == 4 && !whiteasteroid.isWaveSpawned) {
                    whiteasteroid.spawnEnemyWave(whiteAsteroidVector, 4);
                    counter += 1;
                    whiteasteroid.isWaveSpawned = true;
                }
                if (counter == 5 && !whiteasteroid.isWaveSpawned) {
                    whiteasteroid.spawnEnemyWave(whiteAsteroidVector, 5);
                    counter += 1;
                    whiteasteroid.isWaveSpawned = true;
                }
                if (counter == 6 && !whiteasteroid.isWaveSpawned) {
                    whiteasteroid.spawnEnemyWave(whiteAsteroidVector, 6);
                    counter += 1;
                    whiteasteroid.isWaveSpawned = true;
                }
                if (counter == 7 && !whiteasteroid.isWaveSpawned) {
                    whiteasteroid.spawnEnemyWave(whiteAsteroidVector, 7);
                    counter += 1;
                    whiteasteroid.isWaveSpawned = true;
                }
                if (counter == 8 && !whiteasteroid.isWaveSpawned) {
                    whiteasteroid.spawnEnemyWave(whiteAsteroidVector, 8);
                    counter = 8; //Do not add any more waves
                    whiteasteroid.isWaveSpawned = true;
                }
            }
            //Win checking
            //This is done right away, so that if this
            //returns false, checking for a loss still occurs
            if (whiteasteroid.checkForWin(whiteAsteroidVector, whiteasteroid.getLocalEnemyCount())) {
                //We won, :D
                ui.isWin = true;
                ui.isPlaying = false;
            }

            //If the laser is on, drain the player health
            //Also play the sound
            if (laser.isActive) {
                player.playerHealth -= laser.laserDamage;
                audio.laserFire.play();
            }

            //Check the status of our health bar
            //Starts off as green by default, we
            //don't need to check that here.
            if (player.playerHealth <= 70) {
                //Yellow health
                player.healthBar.setFillColor(sf::Color::Yellow);
            }
            if (player.playerHealth <= 30) {
                //red health
                player.healthBar.setFillColor(sf::Color::Red);
            }
            if (player.playerHealth <= 0) {
                //Setting this to false completely
                //stops the game, but wont exit.
                //Game over, you died. ;(
                ui.isWin = false;
                ui.isPlaying = false;
            }

            //Check for enemy collisions against the player
            for (int i = 0; i < whiteasteroid.getMaxEnemies(); ++i) {
                //The player is assumed to be alive or we
                //would not be playing.
                if (whiteAsteroidVector[i]->isActive) {
                    //Slight offset on the Y collision to make it
                    //look like the enemy is actually hitting the player hard
                    if (collisionbox.checkAABBcollision(player.playerSprite.getPosition().x - player.getWidth() / 2,
                                                        player.playerSprite.getPosition().y - player.getHeight() / 2 + 30,
                                                        player.getWidth(), player.getHeight(),
                                                        whiteAsteroidVector[i]->position.x, whiteAsteroidVector[i]->position.y,
                                                        whiteasteroid.size.x, whiteasteroid.size.y)) {

                        //Kill the enemy, damage the player
                        audio.enemyDeath.play();
                        whiteAsteroidVector[i]->isActive = false;
                        player.playerHealth -= 10;
                    }
                }
            }

            //Check for collision of enemies against shield
            for (int i = 0; i < shield.getMaxShieldBlocks(); ++i) {
                for (int j = 0; j < whiteasteroid.getMaxEnemies(); ++j) {
                    //Shield is up and enemy isnt dead
                    if (shieldVector[i]->isChunkActive&& whiteAsteroidVector[j]->isActive) {
                        if (collisionbox.checkAABBcollision(shieldVector[i]->positionX, shieldVector[i]->positionY,
                                                            shield.getWidth(), shield.getHeight(),
                                                            whiteAsteroidVector[j]->position.x, whiteAsteroidVector[j]->position.y,
                                                            whiteasteroid.size.x, whiteasteroid.size.y)) {

                            //Take out a shield chunk and damage the enemy,
                            //Thus allowing the enemy to take out more shield
                            //chunks, ultimately destroying our shield in a cool way.
                            shieldVector[i]->applyDamage(999);
                            whiteAsteroidVector[j]->applyDamage(whiteasteroid.health / 2);
                            if (!whiteAsteroidVector[j]->isActive) {
                                audio.shieldImpact.play();
                            }
                        }
                    }
                }
            }

            //Check collision of enemies against laser
            for (int i = 0; i < whiteasteroid.getMaxEnemies(); ++i) {
                //Ensure we can damage our enemies with the laser
                if (laser.isActive && whiteAsteroidVector[i]->isActive) {
                    if (collisionbox.checkAABBcollision(laser.laserSprite.getPosition().x,
                                                    laser.laserSprite.getPosition().y,
                                                    laser.getWidth(), laser.getHeight(),
                                                    whiteAsteroidVector[i]->position.x, whiteAsteroidVector[i]->position.y,
                                                    whiteasteroid.size.x, whiteasteroid.size.y)) {

                        //Slowly damage the enemy, for
                        //a more realistic laser burn effect
                        whiteAsteroidVector[i]->applyDamage(0.1);
                        if (!whiteAsteroidVector[i]->isActive) {
                            audio.enemyDeath.play();
                        }
                    }
                }
            }

            //Did any of our bullets collide with the enemies?
            //If so, damage the enemy and remove the bullet
            for (int i = 0; i < bullet.getMaxBullets(); ++i) {
                for (int j = 0; j < whiteasteroid.getMaxEnemies(); ++j) {
                    //Ensure our bullet is actually capable of damaging our enemies
                    if (bulletVector[i]->isActive && whiteAsteroidVector[j]->isActive) {
                        if (collisionbox.checkAABBcollision(bulletVector[i]->positionX, bulletVector[i]->positionY,
                                                            bullet.getWidth(), bullet.getHeight(),
                                                            whiteAsteroidVector[j]->position.x, whiteAsteroidVector[j]->position.y,
                                                            whiteasteroid.size.x, whiteasteroid.size.y)) {
                            //Collision detected.
                            bulletVector[i]->isActive = false; //No longer rendered
                            whiteAsteroidVector[j]->applyDamage(bullet.bulletDamage);
                            if (!whiteAsteroidVector[j]->isActive) {
                                audio.enemyDeath.play();
                            }
                        }
                    }
                }
            }

            //If a bullet misses and goes off screen, kill it too
            for (int i = 0; i < bullet.getMaxBullets(); ++i) {
                if (bulletVector[i]->positionY > gmiscfuncandvar.screenHeight || bulletVector[i]->positionY < 0) {
                    bulletVector[i]->isActive = false;
                }
            }

            //If the bullets are dead...
            for (int i = 0; i < bullet.getMaxBullets(); ++i) {
                if (!bulletVector[i]->isActive) {
                    //re-set their initial positions,
                    //so they can be used again
                    bulletVector[i]->positionX = gmiscfuncandvar.screenWidth/ 2;
                    bulletVector[i]->positionY = gmiscfuncandvar.screenHeight - player.getHeight();
                }
            }

            //If an enemy goes off screen, instant loss. Colony destroyed!
            for (int i = 0; i < whiteasteroid.getMaxEnemies(); ++i) {
                if (whiteAsteroidVector[i]->position.y > gmiscfuncandvar.screenHeight) {
                    ui.isWin = false;
                    ui.isPlaying = false;
                }
            }
        }
        //END OF GAME LOGIC, START OF DRAWING STUFF

        //Clear window always
        window.clear(sf::Color::Black);
        //Always draw the background
        window.draw(background);
        //START OF UI EVENTS
        //Must be inside the draw loop,
        //because we are drawing/manipulating
        //our sprites
        if (ui.isMainMenu) {
            ui.isPlaying = false;
            //If we exit the help menu, actually exit from it.
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                ui.isHelpDisplayed = false;
            }
            //Draw all buttons
            window.draw(ui.helpButton);
            window.draw(ui.quitButton);
            window.draw(ui.startButton);
            if (ui.isHelpDisplayed) {
                window.draw(ui.helpPage);
            }
            //If we collide with our start button...
            if (collisionbox.checkAABBcollision(ui.startButton.getPosition().x,
                                                ui.startButton.getPosition().y,
                                                ui.getWidth(), ui.getHeight(),
                                                mouse.getMouseX(), mouse.getMouseY(),
                                                mouse.getWidth(), mouse.getHeight())) {
                //If we press the start button...
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    //Turn everything on...
                    for (int i = 0; i < shield.getMaxShieldBlocks(); ++i) {
                        shieldVector[i]->isChunkActive= true;
                    }

                    //Reset enemy health
                    for (int i = 0; i < whiteasteroid.getMaxEnemies(); ++i){
                        whiteAsteroidVector[i]->health = whiteasteroid.getMaxEnemyHealth();
                    }

                    //Reset the player's health bar
                    player.healthBar.setFillColor(sf::Color::Green);

                    //Reset the player health
                    player.playerHealth = player.playerMaxHealth;

                    //Start playing
                    ui.isWin = false;
                    ui.isPlaying = true;
                    ui.isMainMenu = false;
                }
            }

            //If we press the help button...
            if (collisionbox.checkAABBcollision(ui.helpButton.getPosition().x,
                                    ui.helpButton.getPosition().y,
                                    ui.getWidth(), ui.getHeight(),
                                    mouse.getMouseX(), mouse.getMouseY(),
                                    mouse.getWidth(), mouse.getHeight())) {

                //...turn the page on
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    ui.isHelpDisplayed = true;
                }
            }

            //If we press the quit button...
            if (collisionbox.checkAABBcollision(ui.quitButton.getPosition().x,
                                    ui.quitButton.getPosition().y,
                                    ui.getWidth(), ui.getHeight(),
                                    mouse.getMouseX(), mouse.getMouseY(),
                                    mouse.getWidth(), mouse.getHeight())) {

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    //...Quit
                    window.close();
                }
            }
        } // end ui.isMainMenu

        //Draw our game stuff only when
        //we are playing
        if (ui.isPlaying) {
            //Draw the enemies
            for (int i = 0; i < whiteasteroid.getMaxEnemies(); ++i) {
                if (whiteAsteroidVector[i]->isActive) { //The enemy is NOT dead...
                    //Apply gravity AKA make our enemies move down and towards player
                    whiteAsteroidVector[i]->velocity.y = whiteAsteroidVector[i]->enemyVelocity + whiteasteroid.additionalEnemyVelocity;
                    whiteAsteroidVector[i]->position.x += whiteAsteroidVector[i]->velocity.x * timeStep;
                    whiteAsteroidVector[i]->position.y += whiteAsteroidVector[i]->velocity.y * timeStep;
                    whiteAsteroidVector[i]->sprite.setPosition(whiteAsteroidVector[i]->position.x, whiteAsteroidVector[i]->position.y);
                    window.draw(whiteAsteroidVector[i]->sprite);
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
            if (laser.isActive) {
                window.draw(laser.laserSprite);
            }

            //Draw our shield
            for (int i = 0; i < shield.getMaxShieldBlocks(); ++i) {
                if (shieldVector[i]->isChunkActive) {
                    window.draw(shieldVector[i]->shieldSprite);
                }
            }

            //Draw our player
            window.draw(player.playerSprite);

            //Draw our player's health bar
            window.draw(player.healthBar);
        } else { //ui.isPlaying is now FALSE
            //Remove any stray bullets
            for (int i = 0; i < bullet.getMaxBullets(); ++i) {
                bulletVector[i]->isActive = false;
            }
            //Ensure we are not in the main menu
            if (!ui.isMainMenu) {
                //If we won..
                if (ui.isWin) {
                    //Game victory text and prompt
                    window.draw(text.winText);
                    window.draw(text.spaceTostartText);
                } else { //We have lost
                    //Game over text and prompt
                    text.spaceTostartText.setString("spacebar to quit");
                    window.draw(text.gameOverText);
                    window.draw(text.spaceTostartText);
                    //Stop the music
                    audio.mainMenuTheme.stop();
                }

                //Space bar to re-start event
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    //Do the things that every win would require
                    if (ui.isWin) {
                        //Spawn more enemies
                        whiteasteroid.isWaveSpawned = false;

                        //Reset the enemies health
                        for (int i = 0; i < whiteasteroid.getMaxEnemies(); ++i) {
                            whiteAsteroidVector[i]->health = whiteasteroid.getMaxEnemyHealth();
                        }

                        //Start playing again
                        ui.isPlaying = true;

                        //Always re-set the win variable
                        ui.isWin = false;
                    } else { //We didnt win, must have lost
                        //Pressing spacebar should cause an exit
                        window.close();
                    }
                }
            }
        }
        //Display our window regardless
        //of if we are playing the game or not
        window.display();
    } //End game loop

    std::cout << "Cleaning up shield chunks... Done\n";
    for (std::vector<Shield*>::iterator it = shieldVector.begin(); it != shieldVector.end(); it++){
        delete *it;
    }

    std::cout << "Cleaning up bullet objects... Done\n";
    for (std::vector<Bullet*>::iterator it = bulletVector.begin(); it != bulletVector.end(); it++){
        delete *it;
    }

    std::cout << "Cleaning up enemy objects... Done\n";
    for (std::vector<WhiteAsteroid*>::iterator it = whiteAsteroidVector.begin(); it != whiteAsteroidVector.end(); it++){
        delete *it;
    }
} //End main
