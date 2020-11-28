//
// Created by sevendart on 25.11.20.
//

#include "../include/Character.h"
#include <cmath>

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
    sf::Vector2f nextPosition(currentSprite.getPosition().x + x * speed, currentSprite.getPosition().y + y * speed);
    if (!checkCollisions(currentSprite.getPosition(), nextPosition)) this->currentSprite.move(x * speed, y * speed);
    else {
        currentSprite.move(-2 * x * speed, -2 * y * speed);
    }
}

void Character::setCurrentState(Character::States newState) {
    if (newState != currentState) animations[newState].reset();
    currentState = newState;
}

bool Character::checkCollisions(sf::Vector2f previousPosition, sf::Vector2f nextPosition) {
    int** levelMap = level->levelMap.getLevelMap();
    sf::Vector2i mapPos((int)floor(previousPosition.x / 16), (int)floor(previousPosition.y / 16));
    sf::Vector2i nextMapPos((int)floor(nextPosition.x / 16), (int)floor(nextPosition.y / 16));
    int xDirection = (nextPosition.x >= previousPosition.x) ? 1 : -1;
    int yDirection = (nextPosition.y >= previousPosition.y) ? 1 : -1;
    for (int i = mapPos.x; i * xDirection <= nextMapPos.x * xDirection; i += xDirection)
        for (int j = mapPos.y; j * yDirection <= nextMapPos.y * yDirection; j += yDirection) {
            if (isSolid(levelMap[j + ((yDirection > 0)?2:1)][i + ((xDirection > 0)?1:0)], level->levelMap.getSolidTiles())) return true;
        }
    return false;
}

void Character::getCollision(Character &collisionObject) {

}

bool Character::isSolid(int tile, const std::vector<int> &solidTiles) {
    for (int current: solidTiles) {
        if (current == tile) return true;
    }
    return false;
}


