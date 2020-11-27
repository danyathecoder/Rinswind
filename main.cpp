#include <iostream>
#include <ctime>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include "include/Game.h"

int main()
{
    //stooped at 5th video
    Game game = Game();
    game.run();

    return 0;
}