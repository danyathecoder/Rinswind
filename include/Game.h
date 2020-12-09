//
// Created by danilapoddubny on 19/10/2020.
//

#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

#include "Character.h"
#include "Player.h"
#include "Level.h"

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Button.h"


class Game {
private:
    //variables
    sf::RenderWindow* window;
    sf:: Event event;
    sf::Clock dtClock;
    sf::View *camera;
    Player player;
    int currentLevel;
    std::vector<Level> levels;

    //init functions
    void initWindow();
    void initPlayer();
    void keyboard(float dt);
    void mouse();


public:
    Game();
    virtual ~Game();


    int getLevelNumber() const;

    void setLevelNumber(int levelNumber);

    //functions
    void loadLevel(int number);
    void updateSFMLEvents();
    void update();
    void render();
    void run();
    void input(float dt);

};


#endif //GAME_GAME_H
