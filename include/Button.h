//
// Created by danilapoddubny on 29/11/2020.
//

#ifndef GAME_BUTTON_H
#define GAME_BUTTON_H

#include "SFML/Graphics.hpp"
#include <string>

class Button {
public:
    sf::Texture texture;
    std::string filename;
    sf::Sprite sprite;

    std::function<void(int &currentLevel)> actionPlay;
    std::function<void(sf::RenderWindow*)> actionQuit;

    static Button createButton(float x, float y, const std::string &filename);

    void setTexture();
};



#endif //GAME_BUTTON_H
