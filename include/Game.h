//
// Created by danilapoddubny on 19/10/2020.
//

#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

#include "Player.h"
#include "Level.h"

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


class Game {
private:
    sf:: Event event;
    sf::Clock dtClock;
    std::vector<Level> levels;

    void initWindow();
    void update();
    void render();
    void updateSFMLEvents();
    void input(float dt);
    void keyboard(float dt);
    void mouse();
public:
    sf::View *camera;
    int currentLevel;
    inline static sf::RenderWindow* window;
    inline static Player *player;
    inline static Game *currentGame;
    float volume;
    Game();
    virtual ~Game();
    void initPlayer();
    void setCurrentLevel(int level);
    void loadLevel(int number);
    void run();

    Level *getCurrentLevel();

    void resetPlayer();

    void resetLevel(int level);
};


#endif //GAME_GAME_H
