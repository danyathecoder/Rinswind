//
// Created by danilapoddubny on 29/11/2020.
//

#include "../include/Button.h"
#include "SFML/Graphics.hpp"

Button Button::createButton(float x, float y, const std::string &filename) {
    Button play;
    play.sprite.setPosition(x, y);
    play.filename = filename;
    play.texture.loadFromFile("../resources/" + filename + ".png");
    return play;
}

void Button::setTexture() {
    sprite.setTexture(texture);
}