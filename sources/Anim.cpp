//
// Created by sevendart on 26.11.20.
//

#include "../include/Anim.h"

bool Anim::load(std::string animFile, int count) {
    frames = new sf::Texture[count];
    this->size = count;
    for (int i = 0; i < count; i++) {
        std::string filename = animFile + std::to_string(i) + ".png";
        if (!frames[i].loadFromFile(filename)) return false;
    }
    return true;
}


sf::Texture &Anim::nextFrame(float elapsedTime) {
    currentFrame += (elapsedTime * (float)speed);
    if (currentFrame > (float)size) {
        currentFrame -= (float) size;
        isFinished = true;
    }
    return frames[(int)currentFrame % size];
}

void Anim::reset() {
    currentFrame = 0;
    isFinished = false;
}
