#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
#include "player.h"

/**
*@brief Game Class
*
*@author Michael Moore 2118213
*@author Muhammad Bux 2130436
*
* Class resposnibilities:
*
* Initialisation of the home screen, death screen, winning screen and pause screen.
*
* Controls the collisions that occur between the player sprite and the different game objects.
*
* Initialisation of the rows of ice blocks and enemies.
*
* Initialisation of the igloo.
*
* Initialisation of the temperature counter.
*
* Controls the updating of the elements on the screen while the game is played.

*/
class Game
{
public:

    /** Default constructor.
    */
    Game();

    //Game Functions
    /** This function returns the window.
    */
    const sf::RenderWindow& fetchWindow() const;
    /** This function draws all objects on the screen.
    */
    void renderGame();
    /** This function updates all aspects of the game each frame.
    */
    void updateGame();
    /** This function updates all aspects of the player each frame.
    */
    void updateMyPlayer();
    /** This function draws the player's sprite on the screen.
    */
    void renderMyPlayer();
    /** This function is responsible for checking if any collisions occur between the player and other game objects and return a Boolean.
    */
    bool updateCollisions();

    sf::Font HSFont; /**<Variable that stores the font file used for the text on the home screen. */
    sf::Text HSText; /**<Variable that stores the text used on the home screen. */
    sf::Font TimerFont; /**<Variable that stores the font file used for the timer . */
    sf::Text TimerText; /**<Variable that stores the text used for the timer. */
    sf::Font pauseFont; /**<Variable that stores the font file used for the text on the pause screen. */
    sf::Font youDied; /**<Variable that stores the font file used for the text on the death screen. */
    sf::Text pauseText; /**<Variable that stores the text used on the pause screen. */
    sf::Text deadText; /**<Variable that stores the text used on the death screen. */
    sf::Font winFont; /**<Variable that stores the font file used for the text on the win screen. */
    sf::Text winText; /**<Variable that stores the text used on the win screen. */

    /** This function resets the game variables if the player loses the game.
    */
    void restartGame();

    bool collision; /**<Boolean that states if a collision has occured with a platform, enemy or side of the screen. */
    bool waterCollision; /**<Boolean that states if a collision has occured with the water. */
    bool safeCollision; /**<Boolean that states if a collision has occured with the safe zone. */
    bool dead; /**<Boolean that states if the player has lost. */
    bool pause; /**<Boolean that states if the game has been paused. */

    /** This function allows for the game to be started or for the player to close the game.
    */
    void polling();
    /** This function sets the position, size, colour, font and string displayed on the home screen.
    */
    void initialiseHomeScreen();
    /** This function sets the position, size, colour, font and string displayed on the pause screen.
    */
    void initialisePauseScreen();
    /** This function sets the position, size, colour, font and string displayed for the game timer.
    */
    void initialiseGameTimer();
    /** This function sets the position, size, colour, font and string displayed on the death screen.
    */
    void initialiseDeadScreen();
    /** This function sets the position, size, colour, font and string displayed on the win screen.
    */
    void initialiseWinScreen();
    /** This function sets the position, size, colour and shape of the igloo.
    */
    void initialiseIgloo();
    /** This function records the state of the game when the P key is pressed.
    */
    bool pauseGame();
    /** This function resets the game variables to what they were when the P key was pressed.
    */
    bool resumeGame();

    sf::RenderWindow window; /**<Variable that stores the window to be displayed. */
    sf::Event event; /**<Variable that stores a game event. */
    sf::RectangleShape tile1; /**<Variable storing a rectangle shape. */

    std::vector<sf::ConvexShape> row1; /**<Vector of shapes representing the first row of platforms. */
    std::vector<sf::ConvexShape> row2; /**<Vector of shapes representing the second row of platforms. */
    std::vector<sf::ConvexShape> row3; /**<Vector of shapes representing the third row of platforms. */
    std::vector<sf::ConvexShape> row4; /**<Vector of shapes representing the fourth row of platforms. */

    std::vector<sf::RectangleShape> enemy1; /**<Vector of shapes representing the first row of enemies. */
    std::vector<sf::CircleShape> enemy2; /**<Vector of shapes representing the second row of enemies. */
    std::vector<sf::RectangleShape> enemy3; /**<Vector of shapes representing the third row of enemies. */
    std::vector<sf::CircleShape> enemy4; /**<Vector of shapes representing the fourth row of enemies. */

    std::vector<sf::FloatRect> bound1; /**<Vector of the boundaries of the platforms in the first row. */
    std::vector<sf::FloatRect> bound2; /**<Vector of the boundaries of the platforms in the second row. */
    std::vector<sf::FloatRect> bound3; /**<Vector of the boundaries of the platforms in the third row. */
    std::vector<sf::FloatRect> bound4; /**<Vector of the boundaries of the platforms in the fourth row. */

    std::vector<sf::FloatRect> enemyBound1; /**<Vector of the boundaries of the enemies in the first row. */
    std::vector<sf::FloatRect> enemyBound2; /**<Vector of the boundaries of the enemies in the second row. */
    std::vector<sf::FloatRect> enemyBound3; /**<Vector of the boundaries of the enemies in the third row. */
    std::vector<sf::FloatRect> enemyBound4; /**<Vector of the boundaries of the enemies in the fourth row. */

    sf::FloatRect winBound; /**<Variable holding the boundaries of the complete igloo. */

    std::vector<sf::RectangleShape> igloo; /**<Vector of shapes representing the igloo. */

    float nextIgloo; /**<Variable holding the position of the next block of the igloo. */
    int iglooCount; /**<Variable keeping count of the number of igloo blocks. */

    //Environment graphics
    sf::RectangleShape safe_land; /**<Rectangle variable representing the safe zone. */
    sf::RectangleShape background; /**<Rectangle variable representing the water. */
    sf::RectangleShape sky; /**<Rectangle variable representing the sky. */
    sf::RectangleShape left_spike; /**<Rectangle variable representing the left spike. */
    sf::RectangleShape right_spike; /**<Rectangle variable representing the right spike. */
    sf::Texture left_spike_texture; /**<Texture variable that stores the image of the left spike. */
    sf::Texture right_spike_texture; /**<Texture variable that stores the image of the right spike. */
    sf::Texture grass_texture; /**<Texture variable that stores the image of the grass. */
    sf::Texture water_texture; /**<Texture variable that stores the image of the water. */
    sf::Texture sky_texture; /**<Texture variable that stores the image of the sky. */
    sf::Texture enemy1_texture; /**<Texture variable that stores the image of enemy 1. */
    sf::Texture enemy2_texture; /**<Texture variable that stores the image of enemy 2. */

    /** This function sets the screen size and framerate.
    */
    void initialiseWindow();

    Player* myPlayer; /**<Pointer variable to the Player object. */

    /** This function constructs a Player.
    */
    void initialiseMyPlayer();
    /** This function is responsible for setting the size, position and texture of all the environmental objects.
    */
    void initialiseBlock();

    /** This function is responsible for creating the vector of shapes representing the first row of platforms.
    */
    void initialiseRow1();

    /** This function is responsible for setting the position of the first row of platforms as it wraps around the screen.
    */
    void row1WrapAround();

    /** This function is responsible for creating the vector of shapes representing the second row of platforms.
    */
    void initialiseRow2();

    /** This function is responsible for setting the position of the second row of platforms as it wraps around the screen.
    */
    void row2WrapAround();

    /** This function is responsible for creating the vector of shapes representing the third row of platforms.
    */
    void initialiseRow3();

    /** This function is responsible for setting the position of the third row of platforms as it wraps around the screen.
    */
    void row3WrapAround();

    /** This function is responsible for creating the vector of shapes representing the fourth row of platforms.
    */
    void initialiseRow4();

    /** This function is responsible for setting the position of the fourth row of platforms as it wraps around the screen.
    */
    void row4WrapAround();

    /** This function is responsible for creating the vector of shapes representing the first row of enemies.
    */
    void initialiseEnemy1();

    /** This function is responsible for setting the position of the first row of enemies as it wraps around the screen.
    */
    void enemy1WrapAround();

    /** This function is responsible for creating the vector of shapes representing the second row of enemies.
    */
    void initialiseEnemy2();

    /** This function is responsible for setting the position of the second row of enemies as it wraps around the screen.
    */
    void enemy2WrapAround();

    /** This function is responsible for creating the vector of shapes representing the third row of enemies.
    */
    void initialiseEnemy3();

    /** This function is responsible for setting the position of the third row of enemies as it wraps around the screen.
    */
    void enemy3WrapAround();

    /** This function is responsible for creating the vector of shapes representing the fourth row of enemies.
    */
    void initialiseEnemy4();

    /** This function is responsible for setting the position of the fourth row of enemies as it wraps around the screen.
    */
    void enemy4WrapAround();

    /** This function is responsible for changing the colour of the igloo once all blocks have been added.
    */
    void finalIgloo();
    /** This function is responsible for resetting all the game variables once the player has won the game.
    */
    void checkWin();

    bool inWater; /**<Boolean that states if the player is completely in the water. */
    bool started; /**<Boolean that states if the game has started. */
    bool win; /**<Boolean that states if the player has won the game. */

    sf::Clock GameTime; /**<Clock variable that starts once the game begins. */
    sf::Time TimePassed; /**<Time variable that holds the time that has passed each frame. */
    sf::Time TotalTime; /**<Time variable that holds the maximum time of the game. */
    sf::Time FinalTime; /**<Time variable that holds the time difference between the maximum time and the time that has passed. */
    int DisplayTime; /**<Variable holding the time in seconds that is displayed. */
    sf::Clock PauseClock; /**<Clock variable that starts once the game is paused. */
    sf::Time PauseTime; /**<Time variable that keeps track of the time passed while the game is paused. */

    friend class Player;
private:



};

#endif
