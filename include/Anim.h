//
// Created by sevendart on 26.11.20.
//

#include <SFML/Graphics.hpp>

#ifndef GAME_ANIMATION_H
#define GAME_ANIMATION_H


class Anim {
public:
    bool load(std::string animFile, int count);
    void reset();
    sf::Texture &nextFrame(float elapsedTime);
    bool isFinished = false;
    int speed = 10;
private:
    int size = 0;
    float currentFrame = 0;
    sf::Texture *frames;
};


#endif //GAME_ANIMATION_H
