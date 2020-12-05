//
// Created by sevendart on 26.11.20.
//

#include <SFML/Graphics.hpp>

#ifndef GAME_ANIMATION_H
#define GAME_ANIMATION_H


class Anim {
public:
    std::string name;
    bool load(std::string animFile, int count);
    void reset();
    sf::Texture &nextFrame(float elapsedTime);
private:
    int speed = 10;
    float currentFrame = 0;
    int size = 0;
    bool isReversed = false;
    sf::Texture *frames;
};


#endif //GAME_ANIMATION_H
