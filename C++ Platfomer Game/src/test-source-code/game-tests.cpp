#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include "../game-source-code/Game.h"
#include "../game-source-code/player.h"
#include "doctest.h"

Game testGame;
Player testPlayer;


TEST_CASE("Check that the splash screen text is of the correct colour.")
{
    auto testSCText = testGame.HSText;
    testGame.initialiseHomeScreen();

    CHECK(testSCText.getFillColor() == sf::Color::Magenta);
}

TEST_CASE("Check that the splash screen text appears at the correct position on the screen.")
{
    auto testSCText = testGame.HSText;
    testGame.initialiseHomeScreen();

    CHECK(testSCText.getPosition().x == 550);
    CHECK(testSCText.getPosition().y == 200);
}
TEST_CASE("Check that the text on the splash screen is the correct size.")
{
    auto testSCText = testGame.HSText;
    testGame.initialiseHomeScreen();

    CHECK(testSCText.getCharacterSize() == 30);

}

//Check row movement
TEST_CASE("Check that row 1 is moving right with a displacement of 2.5 pixels per frame")
{
    auto row1_spawnPos = 800.0;
    testGame.started = true;
    testGame.renderGame();
    CHECK(testGame.row1[0].getPosition().x > row1_spawnPos);
    CHECK(testGame.row1[0].getPosition().x == row1_spawnPos+2.5);
}
TEST_CASE("Check that row 2 is moving left with a displacement of 2.5 pixels per frame")
{
    auto row2_spawnPos = 800.0;
    testGame.row2.clear();
    testGame.initialiseRow2();
    testGame.renderGame();
    CHECK(testGame.row2[0].getPosition().x < row2_spawnPos);
    CHECK(testGame.row2[0].getPosition().x == row2_spawnPos-2.5);
}
TEST_CASE("Check that row 3 is moving right with a displacement of 2.5 pixels per frame")
{
    auto row3_spawnPos = 800.0;
    testGame.row3.clear();
    testGame.initialiseRow3();
    testGame.renderGame();
    CHECK(testGame.row3[0].getPosition().x > row3_spawnPos);
    CHECK(testGame.row3[0].getPosition().x == row3_spawnPos+2.5);
}
TEST_CASE("Check that row 4 is moving left with a displacement of 2.5 pixels per frame")
{
    auto row4_spawnPos = 800.0;
    testGame.row4.clear();
    testGame.initialiseRow4();
    testGame.renderGame();
    CHECK(testGame.row4[0].getPosition().x < row4_spawnPos);
    CHECK(testGame.row4[0].getPosition().x == row4_spawnPos-2.5);
}

//Check enemy movement
TEST_CASE("Check that enemy 1 is moving to the right with a displacement of 3 pixels per frame")
{
    testGame.enemy1.clear();
    testGame.initialiseEnemy1();
    auto initial_enemy1_pos = 200;

    testGame.started = true;

    testGame.renderGame();

    CHECK(testGame.enemy1[0].getPosition().x > initial_enemy1_pos);
    CHECK(testGame.enemy1[0].getPosition().x == initial_enemy1_pos+3);

}

TEST_CASE("Check that enemy 2 is moving to the left with a displacement of 3 pixels per frame")
{
    testGame.enemy2.clear();
    testGame.initialiseEnemy2();
    auto initial_enemy2_pos = 1000;

    testGame.started = true;

    testGame.renderGame();

    CHECK(testGame.enemy2[0].getPosition().x < initial_enemy2_pos);
    CHECK(testGame.enemy2[0].getPosition().x == initial_enemy2_pos-3);

}

TEST_CASE("Check that enemy 3 is moving to the right with a displacement of 3 pixels per frame")
{
    testGame.enemy3.clear();
    testGame.initialiseEnemy3();
    auto initial_enemy3_pos = 800;

    testGame.started = true;

    testGame.renderGame();

    CHECK(testGame.enemy3[0].getPosition().x > initial_enemy3_pos);
    CHECK(testGame.enemy3[0].getPosition().x == initial_enemy3_pos+3);

}

TEST_CASE("Check that enemy 4 is moving to the left with a displacement of 3 pixels per frame")
{
    testGame.enemy4.clear();
    testGame.initialiseEnemy4();
    auto initial_enemy4_pos = 800;

    testGame.started = true;

    testGame.renderGame();

    CHECK(testGame.enemy4[0].getPosition().x < initial_enemy4_pos);
    CHECK(testGame.enemy4[0].getPosition().x == initial_enemy4_pos-3);

}
TEST_CASE("Check player moves up and has a negative y velocity")
{
    testPlayer.velocity.y = 0;
    testPlayer.testKeyPressW = true;
    testPlayer.initialisePhysics();
    testPlayer.movePlayer();
    testPlayer.testKeyPressW = false;

    CHECK(testPlayer.moveState == movementState::move_UP);
    CHECK(testPlayer.velocity.y < 0);
}
TEST_CASE("Check player moves down and has a positive y velocity")
{
    testPlayer.velocity.y = 0;
    testPlayer.testKeyPressS = true;
    testPlayer.initialisePhysics();
    testPlayer.movePlayer();
    testPlayer.testKeyPressS = false;

    CHECK(testPlayer.moveState == movementState::move_DOWN);
    CHECK(testPlayer.velocity.y > 0);
}
TEST_CASE("Check player moves right and has a positive x velocity")
{
    testPlayer.velocity.x = 0;
    testPlayer.testKeyPressD = true;
    testPlayer.initialisePhysics();
    testPlayer.movePlayer();
    testPlayer.testKeyPressD = false;

    CHECK(testPlayer.moveState == movementState::move_R);
    CHECK(testPlayer.velocity.x > 0);
}
TEST_CASE("Check player moves left and has a negative x velocity")
{
    testPlayer.velocity.x = 0;
    testPlayer.testKeyPressA = true;
    testPlayer.initialisePhysics();
    testPlayer.movePlayer();
    testPlayer.testKeyPressA = false;

    CHECK(testPlayer.moveState == movementState::move_L);
    CHECK(testPlayer.velocity.x < 0);
}

//Test water

TEST_CASE("Check position of water")
{
    auto testBackground = testGame.background;
    testGame.initialiseBlock();
    CHECK(testBackground.getPosition().x == 0);
    CHECK(testBackground.getPosition().y == 0);
}

TEST_CASE("Check size of water")
{
    auto testBackground = testGame.background;
    testGame.initialiseBlock();
    CHECK(testBackground.getSize() == sf::Vector2f(1600,900));
}

TEST_CASE("Check texture of water")
{
    auto testBackground = testGame.background;
    testGame.initialiseBlock();
    CHECK(testBackground.getTexture() == &testGame.water_texture);
}

//Test sky

TEST_CASE("Check position of sky")
{
    auto testSky = testGame.sky;
    testGame.initialiseBlock();
    CHECK(testSky.getPosition().x == 0);
    CHECK(testSky.getPosition().y == 0);
}

TEST_CASE("Check size of sky")
{
    auto testSky = testGame.sky;
    testGame.initialiseBlock();
    CHECK(testSky.getSize() == sf::Vector2f(1600,50));
}

TEST_CASE("Check texture of sky")
{
    auto testSky = testGame.sky;
    testGame.initialiseBlock();
    CHECK(testSky.getTexture() == &testGame.sky_texture);
}

//Test grass

TEST_CASE("Check position of grass")
{
    auto testGrass = testGame.safe_land;
    testGame.initialiseBlock();
    CHECK(testGrass.getPosition().x == 0);
    CHECK(testGrass.getPosition().y == 0);
}

TEST_CASE("Check size of grass")
{
    auto testGrass = testGame.safe_land;
    testGame.initialiseBlock();
    CHECK(testGrass.getSize() == sf::Vector2f(1600,148));
}

TEST_CASE("Check texture of grass")
{
    auto testGrass = testGame.safe_land;
    testGame.initialiseBlock();
    CHECK(testGrass.getTexture() == &testGame.grass_texture);
}

//Test spikes

TEST_CASE("Check position of left spike")
{
    auto testLSpike = testGame.left_spike;
    testGame.initialiseBlock();
    CHECK(testLSpike.getPosition().x == -40);
    CHECK(testLSpike.getPosition().y == 50);
}

TEST_CASE("Check size of left spike")
{
    auto testLSpike = testGame.left_spike;
    testGame.initialiseBlock();
    CHECK(testLSpike.getSize() == sf::Vector2f(80,1550));
}

TEST_CASE("Check texture of left spike")
{
    auto testLSpike = testGame.left_spike;
    testGame.initialiseBlock();
    CHECK(testLSpike.getTexture() == &testGame.left_spike_texture);
}

TEST_CASE("Check position of right spike")
{
    auto testRSpike = testGame.right_spike;
    testGame.initialiseBlock();
    CHECK(testRSpike.getPosition().x == 1560);
    CHECK(testRSpike.getPosition().y == 50);
}

TEST_CASE("Check size of right spike")
{
    auto testRSpike = testGame.right_spike;
    testGame.initialiseBlock();
    CHECK(testRSpike.getSize() == sf::Vector2f(80,1550));
}

TEST_CASE("Check texture of right spike")
{
    auto testRSpike = testGame.right_spike;
    testGame.initialiseBlock();
    CHECK(testRSpike.getTexture() == &testGame.right_spike_texture);
}

//Test Collisions between player and rows of platforms

TEST_CASE("Check that the collision is registered between the player and row 1 and that the row turns red")
{
    testGame.row1.clear();
    testGame.initialiseRow1();
    testPlayer.initialiseSprite();

    testGame.initialiseMyPlayer();
    testGame.myPlayer->playerSprite.setPosition(800.0,850.0);


    auto isThereCollision = false;
    isThereCollision = testGame.updateCollisions();

    CHECK(isThereCollision == true);
    CHECK(testGame.row1[0].getFillColor() == sf::Color::Red);
    CHECK(testGame.row1[1].getFillColor() == sf::Color::Red);
    CHECK(testGame.row1[2].getFillColor() == sf::Color::Red);
    CHECK(testGame.row1[3].getFillColor() == sf::Color::Red);
}

TEST_CASE("Check that the collision is registered between the player and row 2 and that the row turns red")
{
    testGame.row2.clear();
    testGame.initialiseRow2();
    testPlayer.initialiseSprite();

    testGame.initialiseMyPlayer();
    testGame.myPlayer->playerSprite.setPosition(800.0,662.0);


    auto isThereCollision = false;
    isThereCollision = testGame.updateCollisions();

    CHECK(isThereCollision == true);
    CHECK(testGame.row2[0].getFillColor() == sf::Color::Red);
    CHECK(testGame.row2[1].getFillColor() == sf::Color::Red);
    CHECK(testGame.row2[2].getFillColor() == sf::Color::Red);
    CHECK(testGame.row2[3].getFillColor() == sf::Color::Red);
}

TEST_CASE("Check that the collision is registered between the player and row 3 and that the row turns red")
{
    testGame.row3.clear();
    testGame.initialiseRow3();
    testPlayer.initialiseSprite();

    testGame.initialiseMyPlayer();
    testGame.myPlayer->playerSprite.setPosition(800.0,474.0);


    auto isThereCollision = false;
    isThereCollision = testGame.updateCollisions();

    CHECK(isThereCollision == true);
    CHECK(testGame.row3[0].getFillColor() == sf::Color::Red);
    CHECK(testGame.row3[1].getFillColor() == sf::Color::Red);
    CHECK(testGame.row3[2].getFillColor() == sf::Color::Red);
    CHECK(testGame.row3[3].getFillColor() == sf::Color::Red);
}

TEST_CASE("Check that the collision is registered between the player and row 4 and that the row turns red")
{
    testGame.row4.clear();
    testGame.initialiseRow4();
    testPlayer.initialiseSprite();

    testGame.initialiseMyPlayer();
    testGame.myPlayer->playerSprite.setPosition(800.0,286.0);


    auto isThereCollision = false;
    isThereCollision = testGame.updateCollisions();

    CHECK(isThereCollision == true);
    CHECK(testGame.row4[0].getFillColor() == sf::Color::Red);
    CHECK(testGame.row4[1].getFillColor() == sf::Color::Red);
    CHECK(testGame.row4[2].getFillColor() == sf::Color::Red);
    CHECK(testGame.row4[3].getFillColor() == sf::Color::Red);
}

//Test collisions between player and enemies

TEST_CASE("Check that the collision is registered between the player and enemy 1")
{
    testGame.enemy1.clear();
    testGame.initialiseEnemy1();
    testPlayer.initialiseSprite();

    testGame.initialiseMyPlayer();
    testGame.myPlayer->playerSprite.setPosition(200.0,722.0);


    auto isThereCollision = false;
    isThereCollision = testGame.updateCollisions();

    CHECK(isThereCollision == true);
}

TEST_CASE("Check that the collision is registered between the player and enemy 2")
{
    testGame.enemy2.clear();
    testGame.initialiseEnemy2();
    testPlayer.initialiseSprite();

    testGame.initialiseMyPlayer();
    testGame.myPlayer->playerSprite.setPosition(1000.0,534.0);


    auto isThereCollision = false;
    isThereCollision = testGame.updateCollisions();

    CHECK(isThereCollision == true);
}

TEST_CASE("Check that the collision is registered between the player and enemy 3")
{
    testGame.enemy3.clear();
    testGame.initialiseEnemy3();
    testPlayer.initialiseSprite();

    testGame.initialiseMyPlayer();
    testGame.myPlayer->playerSprite.setPosition(800.0,346.0);


    auto isThereCollision = false;
    isThereCollision = testGame.updateCollisions();

    CHECK(isThereCollision == true);
}

TEST_CASE("Check that the collision is registered between the player and enemy 4")
{
    testGame.enemy4.clear();
    testGame.initialiseEnemy4();
    testPlayer.initialiseSprite();

    testGame.initialiseMyPlayer();
    testGame.myPlayer->playerSprite.setPosition(800.0,158.0);


    auto isThereCollision = false;
    isThereCollision = testGame.updateCollisions();

    CHECK(isThereCollision == true);
}

//Test collisions between player and the sides of the screen

TEST_CASE("Check that the collision is registered between the player and the left side of the screen")
{
    testPlayer.initialiseSprite();

    testGame.initialiseMyPlayer();
    testGame.myPlayer->playerSprite.setPosition(0.0,158.0);


    auto isThereCollision = false;
    isThereCollision = testGame.updateCollisions();

    CHECK(isThereCollision == true);
}

TEST_CASE("Check that the collision is registered between the player and the right side of the screen")
{
    testPlayer.initialiseSprite();

    testGame.initialiseMyPlayer();
    testGame.myPlayer->playerSprite.setPosition(1600.0,158.0);


    auto isThereCollision = false;
    isThereCollision = testGame.updateCollisions();

    CHECK(isThereCollision == true);
}
