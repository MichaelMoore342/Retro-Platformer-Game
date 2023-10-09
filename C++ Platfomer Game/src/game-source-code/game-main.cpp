#include <iostream>
#include <SFML\Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include "Game.h"

int main()

{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    Game myGame;

    while(myGame.fetchWindow().isOpen())
    {
        myGame.polling();
        myGame.pauseGame();
        myGame.resumeGame();
        myGame.restartGame();
        myGame.finalIgloo();
        myGame.checkWin();
        if (myGame.pause == false)
        {
          myGame.updateGame();
          myGame.renderGame();
        }
    }

    return 0;
}



