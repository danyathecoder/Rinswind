//
// Created by danilapoddubny on 29/11/2020.
//

#ifndef GAME_BUTTON_H
#define GAME_BUTTON_H

#include "SFML/Graphics.hpp"
#include <string>

class Button {
private:
public:
    sf::Texture texture;
    float x;
    float y;
    std::string filename;
    sf::Sprite sprite;

    //Button(float x, float y, const std::string &filename);

    float getX() const;
    float getY() const;

    static Button playButton(float x, float y, const std::string &filename);
};



#endif //GAME_BUTTON_H
