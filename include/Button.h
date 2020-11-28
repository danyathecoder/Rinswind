//
// Created by danilapoddubny on 29/11/2020.
//

#ifndef GAME_BUTTON_H
#define GAME_BUTTON_H

#include "SFML/Graphics.hpp"

class Button {
private:
    sf::Texture texture;
    float x;
    float y;
public:
    sf::Sprite playButton(sf::RenderWindow *window, int &levelNumber);
    sf::Sprite exitButton(sf::RenderWindow *window, int &levelNumber);
    sf::Sprite optionsButton(sf::RenderWindow *window, int &levelNumber);
};


#endif //GAME_BUTTON_H
