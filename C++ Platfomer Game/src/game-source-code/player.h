#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SFML\Graphics.hpp>

/**
* This class is a list of potential movements that can be perfomed by the player.
*/

enum class movementState {Idle = 0, move_R, move_L, move_UP, move_DOWN};

/**
*@brief Player Class
*
*@author Michael Moore 2118213
*@author Muhammad Bux 2130436
*
* Class resposnibilities:
*
* Initialise the player sprite.
*
* Control the movement of the player.
*
* Produce different animations for different movements.
*
* Initialise the physics of the sprite.
*
* Control the movement of the player with the ice blocks.
*/
class Player
{
public:

    /** Default constructor.
    */
    Player();


    //Player Functions
    /** Changes to the movement, animations and physics of the player are passed to this function and updated each frame.
    */
    void updatePlayer();
    /** This function draws the sprite on the screen each frame.
    */
    void renderPlayer(sf::RenderTarget& myTarget);
    /** This function takes in the keyboard inputs and sets the direction of the sprite through a vector.
    */
    void movePlayer();
    /** This function cycles through different frames of the image file while the sprite is idle or moving left and right to produce an animation.
    */
    void animationUpdate();
    /** This function ensures the velocity of the player decreases to zero when the player releases the keyboard input.
    */
    void physicsUpdate();
    /** This function sets the velocity of the player using the direction and magnitude passed to it.
    *@param Float Representing direction along the x-axis.
    *@param Float Representing direction along the y-axis.
    */
    void characterMove(const float directionX, const float directionY);
    /** This function matches the velocity of the player with the platforms when a collision is made.
    *@param Boolean States if collision has occured.
    *@param Int Representing the platforms row number.
    *@return Boolean stating if collision was true or false.
    */
    bool MoveWithPlatform(bool Collide, int rowNum);

    /** This function returns the current position of the player as a vector of the x and y coordinates.
    */
    const sf::Vector2f getPosition() const;
    /** This function returns the current boundaries of the player.
    */
    const sf::FloatRect getGlobalBounds() const;

    //Modifiers
    /** This function sets the coordinates of the player's sprite.
    *@param Float Representing the x coordinate.
    *@param Float Representing the y coordinate.
    */
    void setPosition(const float x, const float y);
    /** This function sets the vertical velocity to zero.
    */
    void resetVelocityY();

    bool isCollide = false; /**<Boolean holding state of collisions is set to false by default. */
    bool testKeyPressW; /**<Boolean stating if W key is pressed for test purposes. */
    bool testKeyPressA; /**<Boolean stating if A key is pressed for test purposes. */
    bool testKeyPressS; /**<Boolean stating if S key is pressed for test purposes. */
    bool testKeyPressD; /**<Boolean stating if D key is pressed for test purposes. */

    sf::Vector2f velocity; /**<Vector holding the x and y velocities. */
    movementState moveState; /**<Variable of type movementState. */

    /** This function sets the acceleration, deceleration, maximum and minimum velocity of the player.
    */
    void initialisePhysics();

    sf::Clock jumpTime; /**<Clock variable that keeps track of the time between jumps. */
    sf::Time lastJumpTime; /**<Time variable that records the moment in time when the player last jumped. */
    sf::Time jumpDelay; /**<Time variable that stores the amount of time that each jump is delayed by. */

    /** This function sets the size, position and texture of the player's sprite.
    */
    void initialiseSprite();
    sf::Sprite playerSprite; /**<Sprite variable which can be modified by specific functions. */

private:
    sf::Texture playerTexture; /**<Texture variable that holds the loaded in image of the sprite. */
    sf::IntRect frame; /**<Rectangle variable that designates the portion of the image to be displayed. */
    sf::Clock changeAnimation; /**<Clock variable which keeps track of the time passed during animations. */

    //float moveSpeed;

    /** This function loads in the image file to be used for the sprite's texture.
    */
    void initialiseTexture();
    /** This function resets the animation cycle.
    */
    void initialiseAnimations();
    /** This function sets the movement to idle and resets the jump delay.
    */
    void initialiseVariables();


    //Physics

    float maximumVelocity; /**<Variable holding the maximum velocity allowed by the player. */
    float minimumVelocity; /**<Variable holding the minimum velocity allowed by the player. */
    float acceleration; /**<Variable holding the acceleration of the player */
    float deceleration; /**<Variable holding the deceleration of the player */

    friend class Game;
};

#endif
