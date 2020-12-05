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
//    if (sf::IntRect(x, y, 3c).contains(mouse.getPosition(window[0]))) {
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



float Button::getY() const {
    return y;
}

//Button::Button(float x, float y, const std::string &filename) : x(x), y(y), filename(filename) {
//
//    static sf::Texture texture;
//    texture.loadFromFile("../resources/" + filename + ".png");
//    static sf::Sprite sprite(texture);
//    sprite.setColor(sf::Color::Yellow);
//}

Button Button::playButton(float x, float y, const std::string &filename) {
    Button play;
    play.x = x;
    play.y = y;
    play.texture.loadFromFile("../resources/" + filename + ".png");
    play.sprite.setTexture(play.texture);
    play.sprite.setColor(sf::Color::Yellow);
    return play;
}