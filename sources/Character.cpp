//
// Created by sevendart on 25.11.20.
//

#include "../include/Character.h"


/*void Character::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    printf("%f %f\n", states.transform.);
    target.draw(currentSprite, states);
}*/

void Character::updateSprite(float elapsedTime) {
    currentSprite.setTexture(animations[currentState].nextFrame(elapsedTime));
}


Character::States Character::getCurrentState() const {
    return currentState;
}

void Character::moveCharacter(float x, float y) {
    this->currentSprite.move(x * speed, y * speed);
}

void Character::setCurrentState(Character::States newState) {
    currentState = newState;
    animations[currentState].reset();
}


