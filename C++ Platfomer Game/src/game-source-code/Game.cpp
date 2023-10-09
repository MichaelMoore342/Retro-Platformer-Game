#include <iostream>
#include <SFML\Graphics.hpp>
#include "Game.h"
#include <time.h>
#include <sstream>
#include <cmath>

void Game::initialiseWindow()
{
    window.create(sf::VideoMode(1600, 900), "Game", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
}

const sf::RenderWindow& Game::fetchWindow() const
{
    return window;
}

Game::Game()
{
    initialiseWindow();
    initialiseGameTimer();
    initialiseHomeScreen();
    initialiseDeadScreen();
    initialisePauseScreen();
    initialiseWinScreen();
    initialiseRow1();
    initialiseRow2();
    initialiseRow3();
    initialiseRow4();
    initialiseEnemy1();
    initialiseEnemy2();
    initialiseEnemy3();
    initialiseEnemy4();
    initialiseMyPlayer();
    initialiseBlock();
    started = false;
    win = false;
    nextIgloo = 75;
    iglooCount = 0;
    srand (time(NULL));
}
bool Game::pauseGame()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && dead == false && win == false)
    {
        PauseClock.restart();
        PauseTime = FinalTime;
        pause = true;
        window.clear();
        window.draw(pauseText);
        window.display();
    }
    return pause;
}
bool Game::resumeGame()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && pause == true)
    {
        TotalTime = PauseTime;
        GameTime.restart();
        pause = false;
    }
    return pause;
}
void Game::restartGame()
{
    if (dead == true)
    {
        pause = true;
        window.clear();
        igloo.clear();
        iglooCount = 0;
        nextIgloo = 75;
        window.draw(deadText);
        window.display();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
        {
            window.draw(safe_land);
            pause = false;
            row1.clear();
            initialiseRow1();
            row2.clear();
            initialiseRow2();
            row3.clear();
            initialiseRow3();
            row4.clear();
            initialiseRow4();
            enemy1.clear();
            initialiseEnemy1();
            enemy2.clear();
            initialiseEnemy2();
            enemy3.clear();
            initialiseEnemy3();
            enemy4.clear();
            initialiseEnemy4();
            GameTime.restart();
            TotalTime = sf::seconds(61);

            myPlayer->playerSprite.setPosition(450,60);
            myPlayer->resetVelocityY();
            winBound.height = 0;
            winBound.width = 0;

        }


    }

}

void Game::renderGame()
{

    if (started == false)
    {
        window.clear();
        window.draw(HSText);
    }else
    {
        window.clear();
        //Render game here
        window.draw(background);

        for (int i = 0; i < 4; i++)
        {
            row1[i].move(2.5,0);
            row2[i].move(-2.5,0);
            row3[i].move(2.5,0);
            row4[i].move(-2.5,0);
            window.draw(row1[i]);
            window.draw(row2[i]);
            window.draw(row3[i]);
            window.draw(row4[i]);
        }

        for (int i = 0; i < 3; i++)
        {
            enemy1[i].move(3.0,0);
            enemy2[i].move(-3.0,0);
            enemy3[i].move(3.0,0);
            enemy4[i].move(-3.0,0);
            window.draw(enemy1[i]);
            window.draw(enemy2[i]);
            window.draw(enemy3[i]);
            window.draw(enemy4[i]);
        }

        window.draw(safe_land);
        window.draw(sky);
        window.draw(left_spike);
        window.draw(right_spike);
        window.draw(TimerText);
        for (int i = 0; i < iglooCount; i++)
        {
            window.draw(igloo[i]);
        }
        renderMyPlayer();
    }

    window.display();

}
void Game::polling()
{
    //Poll window events
    while(window.pollEvent(event))
    {
        if((event.type == sf::Event::Closed) ||((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
        {
            window.close();
            break;
        }else if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space) && started == false)
        {
            started = true;
            GameTime.restart();
            TotalTime = sf::seconds(61);
        }

    }
}

void Game::updateGame()
{
    row1WrapAround();
    row2WrapAround();
    row3WrapAround();
    row4WrapAround();

    enemy1WrapAround();
    enemy2WrapAround();
    enemy3WrapAround();
    enemy4WrapAround();

    updateMyPlayer();
    updateCollisions();

    TimePassed = GameTime.getElapsedTime();
    FinalTime = TotalTime - TimePassed;
    DisplayTime = std::round(FinalTime.asSeconds()) -1;
    std::stringstream myStream;

    myStream << DisplayTime;

    std::string display_str;

    myStream >> display_str;

    std::string temp = "Temp:";
    std::string degrees = "C";
    display_str = temp +" " + display_str + degrees;

    TimerText.setString(display_str);

    if(DisplayTime == 0)
    {
        dead = true;
    }

}

void Game::updateMyPlayer()
{
    myPlayer->updatePlayer();
}

void Game::renderMyPlayer()
{
    myPlayer->renderPlayer(window);
}

bool Game::updateCollisions()
{
    safeCollision = false;
    collision = false;
    bound1.clear();
    bound2.clear();
    bound3.clear();
    bound4.clear();
    enemyBound1.clear();
    enemyBound2.clear();
    enemyBound3.clear();
    enemyBound4.clear();
    sf::FloatRect nextPos;
    //Block Collision
    sf::FloatRect playerBounds = myPlayer->getGlobalBounds();
    for (int i = 0; i < 4; i++)
    {
        bound1.push_back(row1[i].getGlobalBounds());
        bound2.push_back(row2[i].getGlobalBounds());
        bound3.push_back(row3[i].getGlobalBounds());
        bound4.push_back(row4[i].getGlobalBounds());
        enemyBound1.push_back(enemy1[i].getGlobalBounds());
        enemyBound2.push_back(enemy2[i].getGlobalBounds());
        enemyBound3.push_back(enemy3[i].getGlobalBounds());
        enemyBound4.push_back(enemy4[i].getGlobalBounds());
    }
    auto safeBound = safe_land.getGlobalBounds();
    nextPos = playerBounds;

    nextPos.left += myPlayer->velocity.x;
    nextPos.top +=  myPlayer->velocity.y;

    auto waterBound = background.getGlobalBounds();

    int rowNum;

    for (int i = 0; i < 4; i++)
    {
      if (bound1[i].intersects(nextPos))
        {
            if(row1[i].getFillColor() != sf::Color::Red)
            {
                initialiseIgloo();
                nextIgloo = nextIgloo - 25;

            }
            for(int k = 0; k<4; k++)
            {
               row1[k].setFillColor(sf::Color::Red);
            }

            rowNum = 1;
            collision = true;
            myPlayer->MoveWithPlatform(collision,rowNum);

        }else if (bound2[i].intersects(nextPos))
        {
            if(row2[i].getFillColor() != sf::Color::Red)
            {
                initialiseIgloo();
                nextIgloo = nextIgloo - 25;

            }
            for(int k = 0; k<4; k++)
            {
               row2[k].setFillColor(sf::Color::Red);
            }

            rowNum = 2;
            collision = true;
            myPlayer->MoveWithPlatform(collision,rowNum);

        }else if (bound3[i].intersects(nextPos))
        {
            if(row3[i].getFillColor() != sf::Color::Red)
            {
                initialiseIgloo();
                nextIgloo = nextIgloo - 25;

            }
            for(int k = 0; k<4; k++)
            {
                row3[k].setFillColor(sf::Color::Red);
            }

            rowNum = 3;
            collision = true;
            myPlayer->MoveWithPlatform(collision,rowNum);

        }else if (bound4[i].intersects(nextPos))
        {
            if(row4[i].getFillColor() != sf::Color::Red)
            {
                initialiseIgloo();
                nextIgloo = nextIgloo - 25;

            }
            for(int k = 0; k<4; k++)
            {
                row4[k].setFillColor(sf::Color::Red);
            }

            rowNum = 4;
            collision = true;
            myPlayer->MoveWithPlatform(collision,rowNum);

        }else if (safeBound.intersects(nextPos))
        {
            safeCollision = true;

        }

    }
    auto leftBound = left_spike.getGlobalBounds();
    auto rightBound = right_spike.getGlobalBounds();

    if (rightBound.intersects(nextPos) || leftBound.intersects(nextPos))
    {
        collision = true;
        dead = true;
    }else
    {
        dead = false;
    }
    for (int i = 0; i < 3; i++)
    {
        if (enemyBound1[i].intersects(nextPos))
            {
                collision = true;
                dead = true;
            }
            else if (enemyBound2[i].intersects(nextPos))
            {
                collision = true;
                dead = true;
            }
            else if(enemyBound3[i].intersects(nextPos))
            {
                collision = true;
                dead = true;
            }
            else if(enemyBound4[i].intersects(nextPos))
            {
                collision = true;
                dead = true;
            }

    }

    if ((collision == false) && (safeCollision == false) && (myPlayer->velocity.y == 0))
    {
       dead = true;
    }

    if (winBound.intersects(nextPos))
    {
        win = true;
    }

    //Bottom Collision
    if (myPlayer->getPosition().y + myPlayer->getGlobalBounds().height > window.getSize().y)
    {
        myPlayer->resetVelocityY();
        myPlayer->setPosition(myPlayer->getPosition().x, window.getSize().y - myPlayer->getGlobalBounds().height) ;
    }

    //Top Collision
    if (myPlayer->getPosition().y  < 0)
    {
        myPlayer->resetVelocityY();
        myPlayer->setPosition(myPlayer->getPosition().x, 0) ;
    }

    //Right Collision
    if (myPlayer->getPosition().x < 0)
    {
        myPlayer->setPosition(0, myPlayer->getPosition().y);
    }
    //Left Collision
    if (myPlayer->getPosition().x + myPlayer->getGlobalBounds().width > 1600)
    {
        myPlayer->setPosition(1600 - myPlayer->getGlobalBounds().width, myPlayer->getPosition().y);
    }

return collision;
}
void Game::initialiseHomeScreen()
{
    //Font initialisation.
    if (!HSFont.loadFromFile("resources/sansation.ttf"))
    {
        std::cout<<"Could not load font."<<std::endl;
    }
    //Initialize Screen
    HSText.setFont(HSFont);
    HSText.setCharacterSize(30);
    HSText.setPosition(550.f,200.f);
    HSText.setFillColor(sf::Color::Magenta);
    HSText.setString("GAME V3.0\nPress A to Move Left\nPress D to move Right\nTap W to move up\nTap S to move down\nPress P to pause the game\nJump on platforms to build your Igloo!\nOnce the igloo changes colour, return to it to win\nDon't fall in the water, avoid enemies and spikes!!!\nDon't let the temperature reach 0!\nPress Space to Continue.");


}

void Game::initialiseGameTimer()
{
    //Font initialisation.
    if (!TimerFont.loadFromFile("resources/sansation.ttf"))
    {
        std::cout<<"Could not load font."<<std::endl;
    }

    TimerText.setFont(TimerFont);
    TimerText.setCharacterSize(30);
    TimerText.setPosition(10.0f,0.0f);
    TimerText.setFillColor(sf::Color::Red);
}

void Game::initialisePauseScreen()
{
    if (!pauseFont.loadFromFile("resources/sansation.ttf"))
    {
        std::cout<<"Could not load font."<<std::endl;
    }
    //Initialize Screen
    pauseText.setFont(pauseFont);
    pauseText.setCharacterSize(30);
    pauseText.setPosition(550.f,350.f);
    pauseText.setFillColor(sf::Color::Green);
    pauseText.setString("PAUSED\nPress R to Resume");

}
void Game::initialiseWinScreen()
{
    if (!winFont.loadFromFile("resources/sansation.ttf"))
    {
        std::cout<<"Could not load font."<<std::endl;
    }
    //Initialize Screen
    winText.setFont(winFont);
    winText.setCharacterSize(30);
    winText.setPosition(550.f,350.f);
    winText.setFillColor(sf::Color::White);
    winText.setString("YOU WIN!!!\nPress N to Start a New Game!\nPress Esc to End Game");

}
void Game::initialiseDeadScreen()
{
    if (!youDied.loadFromFile("resources/sansation.ttf"))
    {
        std::cout<<"Could not load font."<<std::endl;
    }
    //Initialize Screen
    deadText.setFont(youDied);
    deadText.setCharacterSize(30);
    deadText.setPosition(550.f,350.f);
    deadText.setFillColor(sf::Color::Red);
    deadText.setString("YOU DIED!!!\nPress N to start a New Game\nPress Esc to End Game");

}

void Game::initialiseMyPlayer()
{
    myPlayer = new Player();
}
void Game::initialiseBlock()
{
    tile1.setFillColor(sf::Color::Blue);
    tile1.setSize(sf::Vector2f(50,50));
    tile1.setPosition(400,400);

    if(!water_texture.loadFromFile("resources/water.png"))
    {
        std::cout<<"Could not load image"<<std::endl;
    }
    background.setSize(sf::Vector2f(1600,900));
    background.setPosition(0,0);
    background.setTexture(&water_texture);

    if(!sky_texture.loadFromFile("resources/sky.png"))
    {
        std::cout<<"Could not load image"<<std::endl;
    }
    sky.setSize(sf::Vector2f(1600,50));
    sky.setPosition(0,0);
    sky.setTexture(&sky_texture);

    if(!grass_texture.loadFromFile("resources/grass.png"))
    {
        std::cout<<"Could not load image"<<std::endl;
    }
    safe_land.setSize(sf::Vector2f(1600,148));
    safe_land.setPosition(0,0);
    safe_land.setTexture(&grass_texture);

    if(!left_spike_texture.loadFromFile("resources/leftSpike.png"))
    {
        std::cout<<"Could not load image"<<std::endl;
    }

    left_spike.setSize(sf::Vector2f(80,1550));
    left_spike.setPosition(-40,50);
    left_spike.setTexture(&left_spike_texture);

    if(!right_spike_texture.loadFromFile("resources/rightSpike.png"))
    {
        std::cout<<"Could not load image"<<std::endl;
    }

    right_spike.setSize(sf::Vector2f(80,1550));
    right_spike.setPosition(1560,50);
    right_spike.setTexture(&right_spike_texture);
}

void Game::initialiseRow1()
{
    int nextPos1 = 800;

    for (int i = 0; i < 4; i++)
    {
        row1.push_back(sf::ConvexShape());
        row1.back().setPointCount(4);
        row1.back().setPoint(0, sf::Vector2f(0, 0));
        row1.back().setPoint(1, sf::Vector2f(-70, 50));
        row1.back().setPoint(2, sf::Vector2f(130,50));
        row1.back().setPoint(3, sf::Vector2f(200, 0));
        row1.back().setPosition(nextPos1,850);
        nextPos1 = nextPos1 + 275;

    }
}
void Game::row1WrapAround()
{
    for (int i = 0; i < 4; i++)
    {
      if (row1[i].getPosition().x  > 1600)
        {
            row1[i].setPosition(0 - row1[i].getGlobalBounds().width, 850);
        }
    }

}
void Game::initialiseRow2()
{
    int nextPos2 = 800;

    for (int i = 0; i < 4; i++)
    {
        row2.push_back(sf::ConvexShape());
        row2.back().setPointCount(4);
        row2.back().setPoint(0, sf::Vector2f(0, 0));
        row2.back().setPoint(1, sf::Vector2f(-70, 50));
        row2.back().setPoint(2, sf::Vector2f(130,50));
        row2.back().setPoint(3, sf::Vector2f(200, 0));
        row2.back().setPosition(nextPos2,662);
        nextPos2 = nextPos2 - 275;

    }
}
void Game::row2WrapAround()
{
    for (int i = 0; i < 4; i++)
    {
      if (row2[i].getPosition().x + row2[i].getGlobalBounds().width < 0)
        {
            row2[i].setPosition(1600 + row2[i].getGlobalBounds().width, 662);
        }
    }
}
void Game::initialiseRow3()
{
        int nextPos3 = 800;

    for (int i = 0; i < 4; i++)
    {
        row3.push_back(sf::ConvexShape());
        row3.back().setPointCount(4);
        row3.back().setPoint(0, sf::Vector2f(0, 0));
        row3.back().setPoint(1, sf::Vector2f(-70, 50));
        row3.back().setPoint(2, sf::Vector2f(130,50));
        row3.back().setPoint(3, sf::Vector2f(200, 0));
        row3.back().setPosition(nextPos3,474);
        nextPos3 = nextPos3 + 275;

    }

}
void Game::row3WrapAround()
{
    for (int i = 0; i < 4; i++)
    {
      if (row3[i].getPosition().x  > 1600)
        {
            row3[i].setPosition(0 - row3[i].getGlobalBounds().width, 474);
        }
    }

}
void Game::initialiseRow4()
{
        int nextPos4 = 800;

    for (int i = 0; i < 4; i++)
    {
        row4.push_back(sf::ConvexShape());
        row4.back().setPointCount(4);
        row4.back().setPoint(0, sf::Vector2f(0, 0));
        row4.back().setPoint(1, sf::Vector2f(-70, 50));
        row4.back().setPoint(2, sf::Vector2f(130,50));
        row4.back().setPoint(3, sf::Vector2f(200, 0));
        row4.back().setPosition(nextPos4,286);
        nextPos4 = nextPos4 - 275;

    }
}
void Game::row4WrapAround()
{
        for (int i = 0; i < 4; i++)
    {
      if (row4[i].getPosition().x + row4[i].getGlobalBounds().width < 0)
        {
            row4[i].setPosition(1600 + row4[i].getGlobalBounds().width, 286);
        }
    }
}

void Game::initialiseEnemy1()
{
    int nPos1 = 200;

    if(!enemy1_texture.loadFromFile("resources/Enemy1.png"))
    {
        std::cout<<"Could not load image"<<std::endl;
    }

    for (int i = 0; i < 3; i++)
    {
        enemy1.push_back(sf::RectangleShape());
        enemy1.back().setSize(sf::Vector2f(40,40));
        enemy1.back().setPosition(nPos1,722);
        enemy1.back().setTexture(&enemy1_texture);
        nPos1 = nPos1 + 150;

    }
}
void Game::enemy1WrapAround()
{
    for (int i = 0; i < 3; i++)
    {
      if (enemy1[i].getPosition().x  > 1600)
        {
            enemy1[i].setPosition(0 - enemy1[i].getGlobalBounds().width, 722);
        }
    }

}

void Game::initialiseEnemy2()
{
    int nPos2 = 1000;

    if(!enemy2_texture.loadFromFile("resources/Enemy2.png"))
    {
        std::cout<<"Could not load image"<<std::endl;
    }

    for (int i = 0; i < 3; i++)
    {
        enemy2.push_back(sf::CircleShape());
        enemy2.back().setRadius(20.0f);
        enemy2.back().setPosition(nPos2,534);
        enemy2.back().setTexture(&enemy2_texture);
        nPos2 = nPos2 - 150;

    }
}
void Game::enemy2WrapAround()
{
    for (int i = 0; i < 3; i++)
    {
      if (enemy2[i].getPosition().x + enemy2[i].getGlobalBounds().width < 0)
        {
            enemy2[i].setPosition(1600 + enemy2[i].getGlobalBounds().width, 534);
        }
    }
}

void Game::initialiseEnemy3()
{
        int nPos3 = 800;

        if(!enemy1_texture.loadFromFile("resources/Enemy1.png"))
        {
        std::cout<<"Could not load image"<<std::endl;
        }

    for (int i = 0; i < 3; i++)
    {
        enemy3.push_back(sf::RectangleShape());
        enemy3.back().setSize(sf::Vector2f(40,40));
        enemy3.back().setPosition(nPos3,346);
        enemy3.back().setTexture(&enemy1_texture);
        nPos3 = nPos3 + 150;

    }

}
void Game::enemy3WrapAround()
{
    for (int i = 0; i < 3; i++)
    {
      if (enemy3[i].getPosition().x  > 1600)
        {
            enemy3[i].setPosition(0 - enemy3[i].getGlobalBounds().width, 346);
        }
    }

}
void Game::initialiseEnemy4()
{
        int nPos4 = 800;

        if(!enemy2_texture.loadFromFile("resources/Enemy2.png"))
        {
        std::cout<<"Could not load image"<<std::endl;
        }

    for (int i = 0; i < 3; i++)
    {
        enemy4.push_back(sf::CircleShape());
        enemy4.back().setRadius(20.0f);
        enemy4.back().setPosition(nPos4,158);
        enemy4.back().setTexture(&enemy2_texture);
        nPos4 = nPos4 - 150;

    }
}
void Game::enemy4WrapAround()
{
        for (int i = 0; i < 3; i++)
    {
      if (enemy4[i].getPosition().x + enemy4[i].getGlobalBounds().width < 0)
        {
            enemy4[i].setPosition(1600 + enemy4[i].getGlobalBounds().width, 158);
        }
    }
}
void Game::initialiseIgloo()
{
    if (iglooCount <= 3)
    {
        igloo.push_back(sf::RectangleShape());
        igloo.back().setSize(sf::Vector2f(200,25));
        igloo.back().setPosition(1300, nextIgloo);
        igloo.back().setFillColor(sf::Color::Yellow);
        iglooCount = iglooCount + 1;
    }


}
void Game::finalIgloo()
{
    if (iglooCount == 4)
    {
        winBound = igloo[0].getGlobalBounds();
        for (int i = 0; i < 4; i++)
        {
            igloo[i].setFillColor(sf::Color::Magenta);
        }
    }

}
void Game::checkWin()
{
    if (win == true)
    {
        winBound.height = 0;
        winBound.width = 0;
        pause = true;
        window.clear();
        igloo.clear();
        iglooCount = 0;
        nextIgloo = 75;
        window.draw(winText);
        window.display();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
        {
            win = false;
            window.draw(safe_land);
            pause = false;
            row1.clear();
            initialiseRow1();
            row2.clear();
            initialiseRow2();
            row3.clear();
            initialiseRow3();
            row4.clear();
            initialiseRow4();
            enemy1.clear();
            initialiseEnemy1();
            enemy2.clear();
            initialiseEnemy2();
            enemy3.clear();
            initialiseEnemy3();
            enemy4.clear();
            initialiseEnemy4();
            GameTime.restart();
            TotalTime = sf::seconds(61);

            myPlayer->playerSprite.setPosition(450,60);
            myPlayer->resetVelocityY();
        }


    }


}
