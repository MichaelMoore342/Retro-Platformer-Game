#include <iostream>
#include <SFML\Graphics.hpp>
#include "player.h"

void Player::updatePlayer()
{
    movePlayer();
    animationUpdate();
    physicsUpdate();
}

void Player::renderPlayer(sf::RenderTarget& myTarget)
{
    myTarget.draw(playerSprite);
}

Player::Player()
{
    initialiseVariables();
    initialiseTexture();
    initialiseSprite();
    initialiseAnimations();
    initialisePhysics();
    testKeyPressW = false;
    testKeyPressA = false;
    testKeyPressS = false;
    testKeyPressD = false;
}
void Player::initialiseTexture()
{
    if(!playerTexture.loadFromFile("resources/sprite3.png"))
    {
        std::cout<<"Could not load image"<<std::endl;
    }
}

void Player::initialiseSprite()
{

    playerSprite.setTexture(playerTexture);
    frame = sf::IntRect(15,0,80,110);
    playerSprite.setTextureRect(frame);
    playerSprite.setPosition(450,60);
    playerSprite.scale(0.8f,0.8f);
}

void Player::initialiseVariables()
{
    moveState = movementState::Idle;
    jumpDelay = sf::seconds(1);
    lastJumpTime = jumpTime.getElapsedTime() - jumpDelay;
}

void Player::movePlayer()
{
    moveState = movementState::Idle;

            if(((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && ((jumpTime.getElapsedTime() - jumpDelay) > lastJumpTime))  || (testKeyPressW == true))
                {
                    characterMove(0.f, -1.f);
                    moveState = movementState::move_UP;
                    lastJumpTime = jumpTime.getElapsedTime();
                }

            else if(((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && ((jumpTime.getElapsedTime() - jumpDelay) > lastJumpTime))  || (testKeyPressS == true))
                {
                    characterMove(0.f, 1.f);
                    moveState = movementState::move_DOWN;
                    lastJumpTime = jumpTime.getElapsedTime();
                }

            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || (testKeyPressA == true))
                {
                    characterMove(-1.f, 0.f);
                    moveState = movementState::move_L;
                }

            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (testKeyPressD == true))
                {
                    characterMove(1.f, 0.f);
                    moveState = movementState::move_R;
                }
}

void Player::initialiseAnimations()
{
    changeAnimation.restart();
}

void Player::animationUpdate()
{
    if(moveState == movementState::Idle)
    {
            if(changeAnimation.getElapsedTime().asSeconds()>= 0.5f)
            {
                frame.top = 0.f;
                frame.left += 133.f;

                if(frame.left >= 399.f)
                {
                    frame.left = 0;
                }

                changeAnimation.restart();
                playerSprite.setTextureRect(frame);

            }

    }

    else if(moveState == movementState::move_R)
    {
        if(changeAnimation.getElapsedTime().asSeconds()>= 0.1f)
            {
                frame.top = 143.f;
                frame.left += 133.f;

                if(frame.left >= 665.f)
                {
                    frame.left = 0;
                }

                changeAnimation.restart();
                playerSprite.setTextureRect(frame);

            }
            playerSprite.setScale(0.8f,0.8f);
            playerSprite.setOrigin(0.f,0.f);

    }
    else if(moveState == movementState::move_L)
    {
        if(changeAnimation.getElapsedTime().asSeconds()>= 0.1f)
            {
                frame.top = 143.f;
                frame.left += 133.f;

                if(frame.left >= 665.f)
                {
                    frame.left = 0;
                }

                changeAnimation.restart();
                playerSprite.setTextureRect(frame);

            }
            playerSprite.setScale(-0.8f,0.8f);
            playerSprite.setOrigin(playerSprite.getGlobalBounds().width/1.2f, 0.f);
    }

    else
    {
        changeAnimation.restart();
    }



}

void Player::physicsUpdate()
{

    velocity*=deceleration;

    if(std::abs(velocity.x)< minimumVelocity)
    {
        velocity.x = 0.f;
    }
    if(std::abs(velocity.y)< minimumVelocity)
    {
        velocity.y = 0.f;
    }
    playerSprite.move(velocity);
}

void Player::initialisePhysics()
{
    maximumVelocity = 7.0f;
    minimumVelocity = 1.f;
    acceleration = 28.0f;
    deceleration = 0.87f;
}

void Player::characterMove(const float directionX, const float directionY)
{
    velocity.x += directionX*acceleration;

    if(std::abs(velocity.x)>maximumVelocity)
    {
        velocity.x = maximumVelocity*((velocity.x<0.f)? -1.f:1.f);
    }

    velocity.y += directionY*acceleration;

}

bool Player::MoveWithPlatform(bool Collide, int rowNum)
{
    if(Collide == true && (rowNum == 1||rowNum == 3))
    {
        playerSprite.move(2.5,0);
    }

    else if(Collide == true && (rowNum == 2||rowNum == 4))
    {
        playerSprite.move(-2.5,0);

    }


    isCollide = Collide;
    return isCollide;
}

const sf::Vector2f Player::getPosition() const
{

    return playerSprite.getPosition();
}
const sf::FloatRect Player::getGlobalBounds() const
{

    return playerSprite.getGlobalBounds();
}
void Player::setPosition(const float x, const float y)
{
    playerSprite.setPosition(x, y);

}
void Player::resetVelocityY()
{
    velocity.y = 0.f;

}
