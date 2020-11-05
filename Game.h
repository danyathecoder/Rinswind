//
// Created by danilapoddubny on 19/10/2020.
//

#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <iostream>
#include <ctime>
#include <cstdlib>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class Game {
private:
    //variables
    sf:: RenderWindow *window;
    sf:: Event event;
    float dt;
    sf::Clock dtClock;

    //init functions
    void initWindow();
public:
    Game();
    virtual ~Game();

    //functions
    void updateSFMLEvents();
    void update();
    void render();
    void run();
    void updateDt();

};


#endif //GAME_GAME_H
