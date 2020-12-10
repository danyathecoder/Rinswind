//
// Created by sevendart on 10.12.20.
//

#include "../include/Weapon.h"

void Weapon::updateSprite(float elapsedTime) {
    sprite.setTexture(animations[currentState].nextFrame(elapsedTime));
    rotate();
}

void Weapon::setCurrentState(Weapon::States newState) {
    if (newState != currentState) animations[newState].reset();
    currentState = newState;
}

void Weapon::attack() {

}

void Weapon::rotate() {
    sprite.setRotation(90 + angle);
}

Weapon::~Weapon() = default;
