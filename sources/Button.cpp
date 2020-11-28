//
// Created by danilapoddubny on 29/11/2020.
//

#include "../include/Button.h"
#include "SFML/Graphics.hpp"

//sf::Sprite Button::playButton(sf::RenderWindow *window, int &levelNumber) {
//    texture.loadFromFile("../resources/play.png");
//    sf::Sprite button(texture);
//    x = 670;
//    y = 490;
//    button.setPosition(x, y);
//    button.setColor(sf::Color::Yellow);
//    sf::Mouse mouse;
//    if (sf::IntRect(x, y, 350, 150).contains(mouse.getPosition(window[0]))) {
//        button.setColor(sf::Color::Red);
//        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//            levelNumber = 1;
//        }
//    }
//    return button;
//}

float Button::getX() const {
    return x;
}

void Button::setX(float x) {
    Button::x = x;
}

float Button::getY() const {
    return y;
}

void Button::setY(float y) {
    Button::y = y;
}

Button::Button(float x, float y, const std::string &filename) : x(x), y(y), filename(filename) {

    sf::Texture texture;
    texture.loadFromFile("../resources/" + filename + ".png");
    sf::Sprite sprite(texture);
    sprite.setColor(sf::Color::Yellow);
}
