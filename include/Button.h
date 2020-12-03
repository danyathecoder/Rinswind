//
// Created by danilapoddubny on 29/11/2020.
//

#ifndef GAME_BUTTON_H
#define GAME_BUTTON_H

#include "SFML/Graphics.hpp"
#include <string>

class Button {
private:
    sf::Texture texture;
    float x;
    float y;
    std::string filename;
public:
    sf::Sprite sprite;

    Button(float x, float y, const std::string &filename);

    float getX() const;
    float getY() const;
};



#endif //GAME_BUTTON_H
