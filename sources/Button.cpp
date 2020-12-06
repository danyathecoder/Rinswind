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