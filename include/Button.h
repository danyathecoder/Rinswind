//
// Created by danilapoddubny on 29/11/2020.
//

#ifndef GAME_BUTTON_H
#define GAME_BUTTON_H

#include "SFML/Graphics.hpp"
#include <string>
#include "Game.h"
#include "Level.h"

class Button {
public:
    sf::Texture texture;
    std::string filename;
    sf::Sprite sprite;
    std::function<void(Game*)> action;
    sf::Sound sound;

    static Button createButton(float x, float y, const std::string &filename);

    void setTexture();
};



#endif //GAME_BUTTON_H
