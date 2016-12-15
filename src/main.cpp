#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "Player.h"
#include "Cereal.h"
#include "Egg.h"
#include "Toast.h"
#include "Bacon.h"
#include "Shield.h"
#include "CollisionBox.h"
#include "UI.h"
#include "Audio.h"
#include "Laser.h"
#include "Mouse.h"
#include "G_Miscfuncandvar.h"
#include "Text.h"
#include "Resources.h"

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
    backgroundTexture.loadFromFile( PKGDATADIR "/textures/background.png");
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

    //Store our cereal pieces in an std::vector
    //WE MUST REMEMBER TO CLEAN UP ANYTHING
    //CREATED WITH NEW...
    Cereal cereal;
    std::vector<Cereal*> cerealVector;
    for (int i = 0; i < cereal.getMaxCereals(); ++i) {
        cerealVector.push_back(new Cereal());
        //Set the initial positions to match the gun
        cerealVector[i]->positionX = gmiscfuncandvar.screenWidth/ 2;
        cerealVector[i]->positionY = gmiscfuncandvar.screenHeight - player.getHeight();
    }

    //White asteroid/easiest enemy object and pointers
    Egg whiteasteroid;
    std::vector<Egg*> eggVector;
    for (int i = 0; i < whiteasteroid.getMaxEnemies(); ++i) {
        eggVector.push_back(new Egg());
    }

    //Brown asteroid/medium enemy object and pointers;
    Toast toast;
    std::vector<Toast*> toastVector;
    for (int i = 0; i < toast.getMaxEnemies(); ++i) {
        toastVector.push_back(new Toast());
    }

    //Black asteroid/hard enemy object and pointers;
    Bacon bacon;
    std::vector<Bacon*> baconVector;
    for (int i = 0; i < bacon.getMaxEnemies(); ++i) {
        baconVector.push_back(new Bacon());
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
                //cereal.maxRateOfFire to change fire rate
                cereal.rateOfFire -= 0.01f;

                //Current cereal being shot.
                //Used to shoot exactly one cereal at a time.
                static int currentCereal = 0;

                if (cereal.rateOfFire <= 0.0f) { //The our counter expired, so...
                    //Fire our cereals one at a time
                    currentCereal += 1;
                    //If we run out of cereals, re-set to prevent a crash
                    if (currentCereal >= cereal.getMaxCereals()) {
                        currentCereal = 0;
                    }
                    //Allow for our cereal to be rendered, and set the trajectory
                    //According to where the mouse was clicked.
                    cerealVector[currentCereal]->isActive = true;
                    cerealVector[currentCereal]->velocityX = cereal.cerealVelocity *
                            (cos(mouse.getMouseAngle() * gmiscfuncandvar.pi / 180));
                    cerealVector[currentCereal]->velocityY = cereal.cerealVelocity *
                            (sin(mouse.getMouseAngle() * gmiscfuncandvar.pi / 180));

                    //Play our firing sound
                    audio.bulletFire.play();

                    //Re-set the counter
                    cereal.rateOfFire = cereal.maxRateOfFire;
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
                    whiteasteroid.spawnEnemyWave(eggVector, 1);
                    counter += 1;
                    whiteasteroid.isWaveSpawned = true;
                }
                if (counter == 2 && !whiteasteroid.isWaveSpawned) {
                    whiteasteroid.spawnEnemyWave(eggVector, 2);
                    counter += 1;
                    whiteasteroid.isWaveSpawned = true;
                }
                if (counter == 3 && !whiteasteroid.isWaveSpawned) {
                    whiteasteroid.spawnEnemyWave(eggVector, 3);
                    counter += 1;
                    whiteasteroid.isWaveSpawned = true;
                }
                if (counter == 4 && !whiteasteroid.isWaveSpawned) {
                    whiteasteroid.spawnEnemyWave(eggVector, 4);
                    counter += 1;
                    whiteasteroid.isWaveSpawned = true;
                }
                if (counter == 5 && !whiteasteroid.isWaveSpawned) {
                    whiteasteroid.spawnEnemyWave(eggVector, 5);
                    counter += 1;
                    whiteasteroid.isWaveSpawned = true;
                }
                if (counter == 6 && !whiteasteroid.isWaveSpawned) {
                    whiteasteroid.spawnEnemyWave(eggVector, 6);
                    counter += 1;
                    whiteasteroid.isWaveSpawned = true;
                }
                if (counter == 7 && !whiteasteroid.isWaveSpawned) {
                    whiteasteroid.spawnEnemyWave(eggVector, 7);
                    counter += 1;
                    whiteasteroid.isWaveSpawned = true;
                }
                if (counter == 8 && !whiteasteroid.isWaveSpawned) {
                    whiteasteroid.spawnEnemyWave(eggVector, 8);
                    counter = 8; //Do not add any more waves
                    whiteasteroid.isWaveSpawned = true;
                }
            }

            //Spawn our brown asteroids
            if (!toast.isEnemySpawned) {
                toast.spawnRandomEnemy(toastVector);
                toast.isEnemySpawned = true;
            }

            //Spawn the lone black asteroid
            if (!bacon.isEnemySpawned) {
                bacon.spawnEnemy(baconVector);
                bacon.isEnemySpawned = true;
            }

            //Win checking
            //This is done right away, so that if this
            //returns false, checking for a loss still occurs
            if (whiteasteroid.checkForWin(eggVector, whiteasteroid.getLocalEnemyCount())) {
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

            //Check for white asteroid collision against the player
            for (int i = 0; i < whiteasteroid.getMaxEnemies(); ++i) {
                //The player is assumed to be alive or we would not be playing.
                if (eggVector[i]->isActive) {
                    //Slight offset on the Y collision to make it
                    //look like the enemy is actually hitting the player hard
                    if (collisionbox.checkAABBcollision(player.playerSprite.getPosition().x - player.getWidth() / 2,
                                                        player.playerSprite.getPosition().y - player.getHeight() / 2 + 30,
                                                        player.getWidth(), player.getHeight(),
                                                        eggVector[i]->position.x, eggVector[i]->position.y,
                                                        whiteasteroid.size.x, whiteasteroid.size.y)) {

                        //Kill the enemy, damage the player
                        audio.enemyDeath.play();
                        eggVector[i]->isActive = false;
                        player.playerHealth -= 10;
                    }
                }
            }

            //Check for brown asteroid collision against the player
            for (int i = 0; i < toast.getMaxEnemies(); ++i) {
                //The player is assumed to be alive or we would not be playing.
                if (toastVector[i]->isActive) {
                    //Slight offset on the Y collision to make it
                    //look like the enemy is actually hitting the player hard
                    if (collisionbox.checkAABBcollision(player.playerSprite.getPosition().x - player.getWidth() / 2,
                                                        player.playerSprite.getPosition().y - player.getHeight() / 2 + 30,
                                                        player.getWidth(), player.getHeight(),
                                                        toastVector[i]->position.x, toastVector[i]->position.y,
                                                        toast.size.x, toast.size.y)) {

                        //Kill the enemy, damage the player
                        audio.enemyDeath.play();
                        toastVector[i]->isActive = false;
                        player.playerHealth -= 10;
                    }
                }
            }

            //Check for black asteroid collision against the player
            for (int i = 0; i < bacon.getMaxEnemies(); ++i) {
                //The player is assumed to be alive or we would not be playing.
                if (baconVector[i]->isActive) {
                    //Slight offset on the Y collision to make it
                    //look like the enemy is actually hitting the player hard
                    if (collisionbox.checkAABBcollision(player.playerSprite.getPosition().x - player.getWidth() / 2,
                                                        player.playerSprite.getPosition().y - player.getHeight() / 2 + 30,
                                                        player.getWidth(), player.getHeight(),
                                                        baconVector[i]->position.x, baconVector[i]->position.y,
                                                        bacon.size.x, bacon.size.y)) {

                        //Kill the enemy and the player
                        audio.enemyDeath.play();
                        baconVector[i]->isActive = false;
                        //Kill the player by ending the game
                        ui.isWin = false;
                        ui.isPlaying = false;
                    }
                }
            }

            //Check for collision of white enemy against shield
            for (int i = 0; i < shield.getMaxShieldBlocks(); ++i) {
                for (int j = 0; j < whiteasteroid.getMaxEnemies(); ++j) {
                    //Shield is up and enemy isnt dead
                    if (shieldVector[i]->isChunkActive&& eggVector[j]->isActive) {
                        if (collisionbox.checkAABBcollision(shieldVector[i]->positionX, shieldVector[i]->positionY,
                                                            shield.getWidth(), shield.getHeight(),
                                                            eggVector[j]->position.x, eggVector[j]->position.y,
                                                            whiteasteroid.size.x, whiteasteroid.size.y)) {

                            //Take out a shield chunk and damage the enemy,
                            //Thus allowing the enemy to take out more shield
                            //chunks, ultimately destroying our shield in a cool way.
                            shieldVector[i]->applyDamage(999);
                            eggVector[j]->applyDamage(whiteasteroid.health / 2);
                            if (!eggVector[j]->isActive) {
                                audio.shieldImpact.play();
                            }
                        }
                    }
                }
            }

            //Check for collision of brown enemy against shield
            for (int i = 0; i < shield.getMaxShieldBlocks(); ++i) {
                for (int j = 0; j < toast.getMaxEnemies(); ++j) {
                    //Shield is up and enemy isnt dead
                    if (shieldVector[i]->isChunkActive&& toastVector[j]->isActive) {
                        if (collisionbox.checkAABBcollision(shieldVector[i]->positionX, shieldVector[i]->positionY,
                                                            shield.getWidth(), shield.getHeight(),
                                                            toastVector[j]->position.x, toastVector[j]->position.y,
                                                            toast.size.x, toast.size.y)) {

                            shieldVector[i]->applyDamage(999);
                            toastVector[j]->applyDamage(toast.health / 4);
                            if (!toastVector[j]->isActive) {
                                audio.shieldImpact.play();
                            }
                        }
                    }
                }
            }

            //Check collision of white asteroid against laser
            for (int i = 0; i < whiteasteroid.getMaxEnemies(); ++i) {
                //Ensure we can damage our enemies with the laser
                if (laser.isActive && eggVector[i]->isActive) {
                    if (collisionbox.checkAABBcollision(laser.laserSprite.getPosition().x,
                                                    laser.laserSprite.getPosition().y,
                                                    laser.getWidth(), laser.getHeight(),
                                                    eggVector[i]->position.x, eggVector[i]->position.y,
                                                    whiteasteroid.size.x, whiteasteroid.size.y)) {

                        //Slowly damage the enemy, for
                        //a more realistic laser burn effect
                        eggVector[i]->applyDamage(0.1);
                        if (!eggVector[i]->isActive) {
                            audio.enemyDeath.play();
                        }
                    }
                }
            }

            //Check collision of brown asteroid against laser
            for (int i = 0; i < toast.getMaxEnemies(); ++i) {
                //Ensure we can damage our enemies with the laser
                if (laser.isActive && toastVector[i]->isActive) {
                    if (collisionbox.checkAABBcollision(laser.laserSprite.getPosition().x,
                                                    laser.laserSprite.getPosition().y,
                                                    laser.getWidth(), laser.getHeight(),
                                                    toastVector[i]->position.x, toastVector[i]->position.y,
                                                    toast.size.x, toast.size.y)) {

                        //Slowly damage the enemy, for
                        //a more realistic laser burn effect
                        toastVector[i]->applyDamage(1.0);
                        if (!toastVector[i]->isActive) {
                            audio.enemyDeath.play();
                        }
                    }
                }
            }

            //Did any of our cereals collide with the white asteroid?
            for (int i = 0; i < cereal.getMaxCereals(); ++i) {
                for (int j = 0; j < whiteasteroid.getMaxEnemies(); ++j) {
                    //Ensure our cereal is actually capable of damaging our enemies
                    if (cerealVector[i]->isActive && eggVector[j]->isActive) {
                        if (collisionbox.checkAABBcollision(cerealVector[i]->positionX, cerealVector[i]->positionY,
                                                            cereal.getWidth(), cereal.getHeight(),
                                                            eggVector[j]->position.x, eggVector[j]->position.y,
                                                            whiteasteroid.size.x, whiteasteroid.size.y)) {
                            //Collision detected.
                            cerealVector[i]->isActive = false; //No longer rendered
                            eggVector[j]->applyDamage(cereal.cerealDamage);
                            if (!eggVector[j]->isActive) {
                                audio.enemyDeath.play();
                            }
                        }
                    }
                }
            }

            //Did any of our cereals collide with the brown asteroid?
            for (int i = 0; i < cereal.getMaxCereals(); ++i) {
                for (int j = 0; j < toast.getMaxEnemies(); ++j) {
                    //Ensure our cereal is actually capable of damaging our enemies
                    if (cerealVector[i]->isActive && toastVector[j]->isActive) {
                        if (collisionbox.checkAABBcollision(cerealVector[i]->positionX, cerealVector[i]->positionY,
                                                            cereal.getWidth(), cereal.getHeight(),
                                                            toastVector[j]->position.x, toastVector[j]->position.y,
                                                            toast.size.x, toast.size.y)) {
                            //Collision detected.
                            cerealVector[i]->isActive = false; //No longer rendered
                            toastVector[j]->applyDamage(cereal.cerealDamage);
                            if (!toastVector[j]->isActive) {
                                audio.enemyDeath.play();
                            }
                        }
                    }
                }
            }

            //Did any of our cereals collide with the black asteroid?
            for (int i = 0; i < cereal.getMaxCereals(); ++i) {
                for (int j = 0; j < bacon.getMaxEnemies(); ++j) {
                    //Ensure our cereal is actually capable of damaging our enemies
                    if (cerealVector[i]->isActive && baconVector[j]->isActive) {
                        if (collisionbox.checkAABBcollision(cerealVector[i]->positionX, cerealVector[i]->positionY,
                                                            cereal.getWidth(), cereal.getHeight(),
                                                            baconVector[j]->position.x, baconVector[j]->position.y,
                                                            bacon.size.x, bacon.size.y)) {
                            //Collision detected.
                            cerealVector[i]->isActive = false; //No longer rendered
                            baconVector[j]->applyDamage(cereal.cerealDamage);
                            if (!baconVector[j]->isActive) {
                                audio.enemyDeath.play();
                            }
                        }
                    }
                }
            }

            //If a cereal misses and goes off screen, kill it too
            for (int i = 0; i < cereal.getMaxCereals(); ++i) {
                if (cerealVector[i]->positionY > gmiscfuncandvar.screenHeight || cerealVector[i]->positionY < 0) {
                    cerealVector[i]->isActive = false;
                }
            }

            //If the cereals are dead...
            for (int i = 0; i < cereal.getMaxCereals(); ++i) {
                if (!cerealVector[i]->isActive) {
                    //re-set their initial positions,
                    //so they can be used again
                    cerealVector[i]->positionX = gmiscfuncandvar.screenWidth/ 2;
                    cerealVector[i]->positionY = gmiscfuncandvar.screenHeight - player.getHeight();
                }
            }

            //If a white asteroid goes off screen, instant loss! Colony destroyed!
            for (int i = 0; i < whiteasteroid.getMaxEnemies(); ++i) {
                if (eggVector[i]->position.y > gmiscfuncandvar.screenHeight) {
                    ui.isWin = false;
                    ui.isPlaying = false;
                }
            }

            //If a brown asteroid goes off screen, lose all shields!
            for (int i = 0; i < shield.getMaxShieldBlocks(); ++i) {
                for (int j = 0; j < toast.getMaxEnemies(); ++j) {
                    if (toastVector[j]->position.y > gmiscfuncandvar.screenHeight) {
                        shieldVector[i]->isChunkActive = false;
                    }
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
                        eggVector[i]->health = whiteasteroid.getMaxEnemyHealth();
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
            //Draw the black asteroid
            for (int i = 0; i < bacon.getMaxEnemies(); ++i) {
                if (baconVector[i]->isActive) { //The enemy is NOT dead...
                    //Apply gravity AKA make our enemies move down and towards player
                    baconVector[i]->velocity.y = baconVector[i]->enemyVelocity;
                    baconVector[i]->position.x += baconVector[i]->velocity.x * timeStep;
                    baconVector[i]->position.y += baconVector[i]->velocity.y * timeStep;
                    baconVector[i]->sprite.setPosition(baconVector[i]->position.x, baconVector[i]->position.y);
                    window.draw(baconVector[i]->sprite);
                }
            }

            //Draw the white asteroid
            for (int i = 0; i < whiteasteroid.getMaxEnemies(); ++i) {
                if (eggVector[i]->isActive) { //The enemy is NOT dead...
                    //Apply gravity AKA make our enemies move down and towards player
                    eggVector[i]->velocity.y = eggVector[i]->enemyVelocity + whiteasteroid.additionalEnemyVelocity;
                    eggVector[i]->position.x += eggVector[i]->velocity.x * timeStep;
                    eggVector[i]->position.y += eggVector[i]->velocity.y * timeStep;
                    eggVector[i]->sprite.setPosition(eggVector[i]->position.x, eggVector[i]->position.y);
                    window.draw(eggVector[i]->sprite);
                }
            }

            //Draw the brown asteroid
            for (int i = 0; i < toast.getMaxEnemies(); ++i) {
                if (toastVector[i]->isActive) { //The enemy is NOT dead...
                    //Apply gravity AKA make our enemies move down and towards player
                    toastVector[i]->velocity.y = toastVector[i]->enemyVelocity;
                    toastVector[i]->position.x += toastVector[i]->velocity.x * timeStep;
                    toastVector[i]->position.y += toastVector[i]->velocity.y * timeStep;
                    toastVector[i]->sprite.setPosition(toastVector[i]->position.x, toastVector[i]->position.y);
                    window.draw(toastVector[i]->sprite);
                }
            }

            //Draw the cereals
            for (int i = 0; i < cereal.getMaxCereals(); ++i) {
                if (cerealVector[i]->isActive) { //Live cereal, so move it
                    cerealVector[i]->positionX += cerealVector[i]->velocityX * timeStep;
                    cerealVector[i]->positionY += cerealVector[i]->velocityY * timeStep;
                    cerealVector[i]->cerealSprite.setPosition(cerealVector[i]->positionX, cerealVector[i]->positionY);
                    window.draw(cerealVector[i]->cerealSprite);
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
            //Remove any stray cereals
            for (int i = 0; i < cereal.getMaxCereals(); ++i) {
                cerealVector[i]->isActive = false;
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

                        //Reset the white asteroids health
                        for (int i = 0; i < whiteasteroid.getMaxEnemies(); ++i) {
                            eggVector[i]->health = whiteasteroid.getMaxEnemyHealth();
                        }

                        //Reset and respawn our brown asteroids
                        for (int i = 0; i < toast.getMaxEnemies(); ++i) {
                            toastVector[i]->isActive = false;
                            toastVector[i]->health = toastVector[i]->maxHealth;
                        }
                        toast.isEnemySpawned = false;

                        //Reset and respawn the black asteroid
                        for (int i = 0; i < bacon.getMaxEnemies(); ++i) {
                            baconVector[i]->isActive = false;
                            baconVector[i]->health = baconVector[i]->maxHealth;
                        }
                        bacon.isEnemySpawned = false;

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

    //Clean up anything that was new'd at the top.
    std::cout << "Cleaning up shield chunks... Done\n";
    for (std::vector<Shield*>::iterator it = shieldVector.begin(); it != shieldVector.end(); it++){
        delete *it;
    }

    std::cout << "Cleaning up cereal objects... Done\n";
    for (std::vector<Cereal*>::iterator it = cerealVector.begin(); it != cerealVector.end(); it++){
        delete *it;
    }

    std::cout << "Cleaning up white asteroid... Done\n";
    for (std::vector<Egg*>::iterator it = eggVector.begin(); it != eggVector.end(); it++){
        delete *it;
    }

    std::cout << "Cleaning up brown asteroid... Done\n";
    for (std::vector<Toast*>::iterator it = toastVector.begin(); it != toastVector.end(); it++){
        delete *it;
    }

    std::cout << "Cleaning up black asteroid... Done\n";
    for (std::vector<Bacon*>::iterator it = baconVector.begin(); it != baconVector.end(); it++){
        delete *it;
    }
} //End main
