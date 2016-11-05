#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "include/Bullet.h"
#include "include/Enemy.h"
#include "include/Shield.h"
#include "include/CollisionBox.h"
#include "include/UI.h"

//Allow the the use of pi
constexpr double pi_value() { return M_PI; }
double pi = pi_value();

//Are we in "debug" mode
bool IS_DEBUG = false;

//Calculate a quadratic equation
sf::Vector2f calculateQuadratic(float n)
{
    sf::Vector2f tempVector;
    float y = 370 + (2.2 * (std::pow(n, 2)) / 800);
    float x = 390 + n;
    tempVector.x = x;
    tempVector.y = y;
    return tempVector;
}

//Calculate the mouse angle, in degrees
float calculateMouseAngle(float mouseX, float mouseY, float positionX, float positionY)
{
    float angle = std::atan2(mouseY - positionY, mouseX - positionX);
    angle = angle * 180 / pi;

    if (angle < 0)
    {
        angle = 360 -(-angle);
    }

    return angle;
}

int main()
{
    //Frame rate limiter
    const float timeStep = 1/60.0f;

    //Our window and event union
    const int SCREEN_HEIGHT = 600;
    const int SCREEN_WIDTH = 800;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Spacey Rocks");
    sf::Event event;

    //Our collision detection object
    CollisionBox collisionbox;

    //Our user interface object
    UI ui;

    //Shoot sound
    sf::SoundBuffer buffer;
    buffer.loadFromFile("../effects/shoot.wav");
    sf::Sound bulletShoot;
    bulletShoot.setBuffer(buffer);

    //Our music
    sf::Music music;
    music.openFromFile("../music/main_theme.wav");
    //Loop it
    music.setLoop(true);
    //Play it
    music.play();

    //Our square font
    sf::Font blockFont;
    blockFont.loadFromFile("../fonts/ehsmb.ttf");

    //Our game over text
    sf::Text gameOverText;
    gameOverText.setFont(blockFont);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(110);
    gameOverText.setColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Regular);
    gameOverText.setPosition(SCREEN_WIDTH / 8, SCREEN_HEIGHT / 3);

    //Our space to start text
    sf::Text spaceTostartText;
    spaceTostartText.setFont(blockFont);
    spaceTostartText.setString("space bar to start");
    spaceTostartText.setCharacterSize(55);
    spaceTostartText.setColor(sf::Color::Yellow);
    spaceTostartText.setStyle(sf::Text::Regular);
    spaceTostartText.setPosition(SCREEN_WIDTH / 8, SCREEN_HEIGHT / 2);

    //Our victory text
    sf::Text winText;
    winText.setFont(blockFont);
    winText.setString("You WIN!!");
    winText.setCharacterSize(110);
    winText.setColor(sf::Color::Green);
    winText.setStyle(sf::Text::Regular);
    winText.setPosition(SCREEN_WIDTH / 8, SCREEN_HEIGHT / 3);

    //Our background image
    sf::Sprite background;
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../textures/bg.png");
    background.setTexture(backgroundTexture);

    //Our player's "health bar"
    //Change the color of the bar to
    //represent the players health
    sf::RectangleShape playerHealthBar;
    playerHealthBar.setSize(sf::Vector2f(20, 50));
    //The player starts with a full (green) HP bar
    playerHealthBar.setFillColor(sf::Color::Green);
    //Position the bar on our player structure
    playerHealthBar.setPosition(SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT - 75);

    //Our stationary player
    sf::Sprite player;
    sf::Texture playerTexture;
    playerTexture.loadFromFile("../textures/moonbase.png");
    player.setTexture(playerTexture);
    //Move the  to the bottom middle of the screen
    player.setOrigin(playerTexture.getSize().x / 2, playerTexture.getSize().y / 2);
    player.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - playerTexture.getSize().y / 2);
    //Our players constant max health,
    //used to re-set the game
    const float playerMaxHealth = 100.0f;
    //Our modify-able player health
    float playerHealth = playerMaxHealth;

    //Our laser sprite
    sf::Sprite laser;
    sf::Texture laserTexture;
    laserTexture.loadFromFile("../textures/laser.png");
    laser.setTexture(laserTexture);
    //Position the laser at the bottom, because it shoots
    //from the sides of our moon hut
    laser.setPosition(0, SCREEN_HEIGHT - 50);
    //a boolean value to determine when the lasers is in use or not
    bool isLaserOn = false;

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
    //Did we spawn a wave?
    bool isWaveSpawned = false;

    //SAME AS ABOVE BUT FOR OUR ENEMIES
    //REMEMBER TO CLEAN THIS UP
    Enemy enemy;
    std::vector<Enemy*> enemyVector;
    for (int i = 0; i < enemy.getMaxEnemies(); ++i) {
        enemyVector.push_back(new Enemy());
    }

    Shield shield;
    //CLEAN THIS UP AS WELL
    std::vector<Shield*> shieldVector;
    for (int i = 0; i < shield.getMaxShieldBlocks(); ++i) {
        shieldVector.push_back(new Shield());
        //Enable the shield
        shieldVector[i]->isShieldUp = true;
        shieldVector[i]->shieldSprite.setPosition(shieldVector[i]->positionX, shieldVector[i]->positionY);
    }

    //Position the shield blocks
    static int counter = 0;
    for (float i = -300; i <= 300; i += 10) {
        float x = calculateQuadratic(i).x;
        float y = calculateQuadratic(i).y;
        shieldVector[counter]->positionX = x;
        shieldVector[counter]->positionY = y;
        shieldVector[counter]->shieldSprite.setPosition(shieldVector[counter]->positionX,
                                                        shieldVector[counter]->positionY);
        if (counter == shield.getMaxShieldBlocks() - 1) {
            break;
        }
        counter += 1;
    }

    //Our mouse angle used for bullet paths
    static float mouseAngle = 0.0f;

    //Our mouse X and Y values
    //Used in the main menu and when
    //shooting bullets.
    float mouseX;
    float mouseY;

    /* * * * MAIN LOOP * * * */
    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseMoved) {
                //Calculate the mouse position first
                mouseX = event.mouseMove.x;
                mouseY = event.mouseMove.y;
                mouseAngle = calculateMouseAngle(mouseX, mouseY,
                        (SCREEN_WIDTH / 2), (SCREEN_HEIGHT - playerTexture.getSize().y));
            }
            //If we release right mouse, turn off laser
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    isLaserOn = false;
                }
            }
        } //End event loop

        //Pressed escape, so...
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            //Pause the game and return to main menu
            ui.isMainMenu = true;
        }

        //Mouse down and moved events
        //Shoot with left mouse
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
                bulletVector[currentBullet]->velocityX = bullet.getConstantVelocity() * (cos(mouseAngle * pi / 180));
                bulletVector[currentBullet]->velocityY = bullet.getConstantVelocity() * (sin(mouseAngle * pi / 180));

                //Play our shoot sound
                bulletShoot.play();

                //Re-set the counter
                bullet.rateOfFire = bullet.maxRateOfFire;
            }
        }

        //Mouse right event
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            isLaserOn = true;
        }

        //END OF EVENTS, START OF GAME LOGIC

        //Handle our music here as this seems
        //to be the only place it works...
        //Not in the main menu, mute music
        if (!ui.isMainMenu) {
            music.setVolume(0);
        } else {
            music.setVolume(100);
        }

        //If the laser is on, drain the player health
        if (isLaserOn) {
            playerHealth -= 0.025;
        }

        //As the player takes damage, change the health bar color
        //Starts off by default as green, we don't account
        //for that condition here.
        if (playerHealth <= 70) {
            //Yellow health
            playerHealthBar.setFillColor(sf::Color::Yellow);
        }
        if (playerHealth <= 30) {
            //red health
            playerHealthBar.setFillColor(sf::Color::Red);
        }
        if (playerHealth <= 0) {
            //Setting this to false completely
            //stops the game, but wont exit.
            //Game over, you died. ;(
            ui.isPlaying = false;
        }

        //Check for enemy collisions against the player
        for (int i = 0; i < enemy.getMaxEnemies(); ++i) {
            if (!enemyVector[i]->isDead) {
                if (collisionbox.checkAABBcollision(player.getPosition().x - playerTexture.getSize().x / 2,
                                                    player.getPosition().y - playerTexture.getSize().y / 2 + 30,
                                                    playerTexture.getSize().x, playerTexture.getSize().y,
                                                    enemyVector[i]->positionX, enemyVector[i]->positionY,
                                                    enemy.getWidth(), enemy.getHeight())) {
                    //Kill the enemy, damage the player
                    enemyVector[i]->isDead = true;
                    playerHealth -= 10;
                }
            }
        }

        //Check for collision of enemies against shield
        for (int i = 0; i < shield.getMaxShieldBlocks(); ++i) {
            for (int j = 0; j < enemy.getMaxEnemies(); ++j) {
                //Shield is up and enemy isnt dead
                if (shieldVector[i]->isShieldUp && !enemyVector[j]->isDead) {
                    if (collisionbox.checkAABBcollision(shieldVector[i]->positionX, shieldVector[i]->positionY,
                                                        shield.getWidth(), shield.getHeight(),
                                                        enemyVector[j]->positionX, enemyVector[j]->positionY,
                                                        enemy.getWidth(), enemy.getHeight())) {

                        //Take out a shield chunk and damage the enemy,
                        //Thus allowing it to take out more shield
                        //chunks thus destroying our shield in a cool way.
                        shieldVector[i]->applyDamage(999);
                        enemyVector[j]->applyDamage(30.0);
                    }
                }
            }
        }

        //Check collision of enemies against laser
        if (isLaserOn) {
            for (int i = 0; i < enemy.getMaxEnemies(); ++i) {
                if (collisionbox.checkAABBcollision(laser.getPosition().x, laser.getPosition().y,
                                                laserTexture.getSize().x, laserTexture.getSize().y,
                                                enemyVector[i]->positionX, enemyVector[i]->positionY,
                                                enemy.getWidth(), enemy.getHeight())) {

                    //Slowly damage the enemy, for
                    //a more realistic effect
                    enemyVector[i]->applyDamage(0.1);
                }
            }
        }

        //Did any of our bullets collide with the enemies?
        //If so, damage the enemy and remove the bullet
        for (int i = 0; i < bullet.getMaxBullets(); ++i) {
            for (int j = 0; j < enemy.getMaxEnemies(); ++j) {
                //Ensure our bullet is actually capable of damaging our objects
                if (bulletVector[i]->isActive && !enemyVector[j]->isDead) {
                    if (collisionbox.checkAABBcollision(bulletVector[i]->positionX, bulletVector[i]->positionY,
                                                        bullet.getWidth(), bullet.getHeight(),
                                                        enemyVector[j]->positionX, enemyVector[j]->positionY,
                                                        enemy.getWidth(), enemy.getHeight())) {
                        //Collision detected.
                        bulletVector[i]->isActive = false; //No longer rendered
                        enemyVector[j]->applyDamage(bullet.bulletDamage);
                    }
                }
            }
        }

        //If a bullet misses and goes off screen, kill it too
        for (int i = 0; i < bullet.getMaxBullets(); ++i) {
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

        //If an enemy misses and goes off screen, kill it too
        //Instant loss, colony destroyed!
        for (int i = 0; i < enemy.getMaxEnemies(); ++i) {
            if (enemyVector[i]->positionY > SCREEN_HEIGHT) {
                enemyVector[i]->isDead = true;
                ui.isWin = false;
                ui.isPlaying = false;
            }
        }

        //Win checking
        if (isWaveSpawned) {
            if (enemy.checkForWin(enemyVector)) {
                ui.isWin = true;
                ui.isPlaying = false;
            }
        }

        //END OF GAME LOGIC, START OF DRAWING STUFF

        //Clear window always
        window.clear(sf::Color::Black);
        //Always draw the background
        window.draw(background);
        //Allways allow for the debug squares
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
            //The start box collides with the mouse
            //We add a width/height to the mouse
            //for the purpose of collision.
            int mouseWidth = 5;
            int mouseHeight = 5;
            //MouseX and mouseY are from way further up. This works but
            //I don't like the idea of using global variables...
            if (collisionbox.checkAABBcollision(ui.startButton.getPosition().x,
                                                ui.startButton.getPosition().y,
                                                ui.getWidth(), ui.getHeight(),
                                                mouseX, mouseY, mouseWidth, mouseHeight)) {
                //We click on the start button...
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    //Turn everything on...
                    for (int i = 0; i < shield.getMaxShieldBlocks(); ++i) {
                        shieldVector[i]->isShieldUp = true;
                    }

                    //Reset enemy health
                    for (int i = 0; i < enemy.getMaxEnemies(); ++i){
                        enemyVector[i]->enemyHealth = enemy.getMaxEnemyHealth();
                    }

                    //Reset the player's health bar
                    playerHealthBar.setFillColor(sf::Color::Green);

                    //Reset the player health
                    playerHealth = playerMaxHealth;

                    //Start playing
                    ui.isWin = false;
                    ui.isPlaying = true;
                    ui.isMainMenu = false;
                }
            }

            //We press the help button
            if (collisionbox.checkAABBcollision(ui.helpButton.getPosition().x,
                                    ui.helpButton.getPosition().y,
                                    ui.getWidth(), ui.getHeight(),
                                    mouseX, mouseY, mouseWidth, mouseHeight)) {

                //Turn the page on
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    ui.isHelpDisplayed = true;
                }
            }

            //If we press the quit button
            if (collisionbox.checkAABBcollision(ui.quitButton.getPosition().x,
                                    ui.quitButton.getPosition().y,
                                    ui.getWidth(), ui.getHeight(),
                                    mouseX, mouseY, mouseWidth, mouseHeight)) {

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    //Quit
                    window.close();
                }
            }
        } // end ui.isMainMenu

        //Running our actual game
        if (ui.isPlaying) {
            //Spawn a wave
            if (!isWaveSpawned) {
                //Spawn 1 wave at a time
                static int counter = 1;
                //Because our counter variable is not
                //A constant expression, we must use
                //if statements instead of case, or
                //we get a compiler error.
                if (counter == 1 && !isWaveSpawned) {
                    enemy.spawnEnemyWave(enemyVector, 1);
                    counter += 1;
                    isWaveSpawned = true;
                }
                if (counter == 2 && !isWaveSpawned) {
                    enemy.spawnEnemyWave(enemyVector, 2);
                    counter += 1;
                    isWaveSpawned = true;
                }
                if (counter == 3 && !isWaveSpawned) {
                    enemy.spawnEnemyWave(enemyVector, 3);
                    counter += 1;
                    isWaveSpawned = true;
                }
                if (counter == 4 && !isWaveSpawned) {
                    enemy.spawnEnemyWave(enemyVector, 4);
                    counter += 1;
                    isWaveSpawned = true;
                }
                if (counter == 5 && !isWaveSpawned) {
                    enemy.spawnEnemyWave(enemyVector, 5);
                    counter += 1;
                    isWaveSpawned = true;
                }
                if (counter == 6 && !isWaveSpawned) {
                    enemy.spawnEnemyWave(enemyVector, 6);
                    counter += 1;
                    isWaveSpawned = true;
                }
                if (counter == 7 && !isWaveSpawned) {
                    enemy.spawnEnemyWave(enemyVector, 7);
                    counter += 1;
                    isWaveSpawned = true;
                }
                if (counter == 8 && !isWaveSpawned) {
                    enemy.spawnEnemyWave(enemyVector, 8);
                    counter += 1;
                    isWaveSpawned = true;
                }
                //This triggers the default case from our
                //spawn enemy function, on purpose.
                if (counter == 9 && !isWaveSpawned) {
                    enemy.spawnEnemyWave(enemyVector, 9);
                    counter = 9; //Do not increment the counter anymore
                    isWaveSpawned = true;
                }
            }

            //Draw the enemies
            for (int i = 0; i < enemy.getMaxEnemies(); ++i) {
                if (!enemyVector[i]->isDead) { //The enemy is NOT dead...
                    enemyVector[i]->velocityY = enemyVector[i]->getVelocity(); //Gravity on the Y axis
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
            for (int i = 0; i < shield.getMaxShieldBlocks(); ++i) {
                if (shieldVector[i]->isShieldUp) {
                    window.draw(shieldVector[i]->shieldSprite);
                }
            }

            //Draw our player
            window.draw(player);

            //Draw our player's health bar
            window.draw(playerHealthBar);
        } else {
            //Kill everything because we are no longer playing
            for (int i = 0; i < shield.getMaxShieldBlocks(); ++i) {
                shieldVector[i]->isShieldUp = false;
            }

            for (int i = 0; i < bullet.getMaxBullets(); ++i) {
                bulletVector[i]->isActive = false;
            }

            //Ensure we are not in the main menu
            if (!ui.isMainMenu) {
                //If we won..
                if (ui.isWin) {
                    //Game victory text
                    window.draw(winText);
                    //Space to start prompt
                    window.draw(spaceTostartText);
                } else {
                    //Game over text and prompt
                    window.draw(gameOverText);
                    window.draw(spaceTostartText);
                }

                //Space bar to re-start event
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    //Spawn more enemies
                    isWaveSpawned = false;

                    //Turn everything back on...
                    for (int i = 0; i < shield.getMaxShieldBlocks(); ++i) {
                        shieldVector[i]->isShieldUp = true;
                    }

                    //Re-set the enemy parameters
                    for (int i = 0; i < enemy.getMaxEnemies(); ++i) {
                        enemyVector[i]->enemyHealth = enemy.getMaxEnemyHealth();
                    }

                    //only re-set enemies that need re-setting
                    for (int i = 0; i < enemy.getAdjustedMaxEnemies(); ++i) {
                        enemyVector[i]->isDead = false;
                    }

                    //Reset the player's health bar
                    playerHealthBar.setFillColor(sf::Color::Green);

                    //Reset the player health
                    playerHealth = playerMaxHealth;

                    //Re-set the win
                    ui.isWin = false;

                    //Start playing again
                    ui.isPlaying = true;
                }
            }
        }
        //Display our window regardless
        //of if we are playing the game or not
        window.display();
    } //End game loop

    std::cout << "Cleaning up shields... Done\n";
    for (std::vector<Shield*>::iterator it = shieldVector.begin(); it != shieldVector.end(); it++){
        delete *it;
    }

    std::cout << "Cleaning up bullets... Done\n";
    for (std::vector<Bullet*>::iterator it = bulletVector.begin(); it != bulletVector.end(); it++){
        delete *it;
    }

    std::cout << "Cleaning up enemies... Done\n";
    for (std::vector<Enemy*>::iterator it = enemyVector.begin(); it != enemyVector.end(); it++){
        delete *it;
    }
} //End main
