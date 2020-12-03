//
// Created by sevendart on 25.11.20.
//

#include "../include/Level.h"
#include "../include/Character.h"
#include <cmath>

void Character::updateSprite(float elapsedTime) {
    currentSprite.setTexture(animations[currentState].nextFrame(elapsedTime));
}


Character::States Character::getCurrentState() const {
    return currentState;
}

void Character::moveCharacter(float x, float y) {
    sf::Vector2f dir;
    dir.x = (float)currentSprite.getTexture()->getSize().x / 2;
    if (x < 0) dir.x *= -1;
    dir.y = (float)currentSprite.getTexture()->getSize().y / 2;
    if (y < 0) dir.y *= 0;
    sf::Vector2f nextPosition(currentSprite.getPosition().x + x * speed + dir.x, currentSprite.getPosition().y + y * speed + dir.y);
    if (!checkCollisions(currentSprite.getPosition(), nextPosition))
        this->currentSprite.move(x * speed, y * speed);
    else {
        currentSprite.move(-1 * x * speed, -1 * y * speed);
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
    int xDir = (nextPosition.x >= previousPosition.x) ? 1 : -1;
    int yDir = (nextPosition.y >= previousPosition.y) ? 1 : -1;
    for (int i = mapPos.x; i * xDir <= nextMapPos.x * xDir; i += xDir)
        for (int j = mapPos.y; j * yDir <= nextMapPos.y * yDir; j += yDir) {
            if (isSolid(levelMap[j][i], level->levelMap.getSolidTiles())) return true;
        }
    for (auto &character: level->characters) {
        sf::Vector2f lup = character.currentSprite.getPosition();
        sf::Vector2u size = character.currentSprite.getTexture()->getSize();
        lup.x -= (float)size.x / 2;
        lup.y -= (float)size.y / 2;
        if (isContains(nextPosition, size, lup)) {
            character.getCollision(this);
            return true;
        }
    }
    return false;
}

bool Character::isContains(sf::Vector2f checking, sf::Vector2u size, sf::Vector2f leftUpPoint) {
    printf("checking: %f %f\n", checking.x, checking.y);
    printf("size: %d %d\n", size.x, size.y);
    printf("lup: %f %f\n", leftUpPoint.x, leftUpPoint.y);
    if (checking.x >= leftUpPoint.x && checking.x <= leftUpPoint.x + size.x)
        if (checking.y >= leftUpPoint.y && checking.y <= leftUpPoint.y + size.y)
            return true;
    return false;
}

void Character::getCollision(Character* collisionObject) {

}

bool Character::isSolid(int tile, const std::vector<int> &solidTiles) {
    for (int current: solidTiles) {
        if (current == tile) return true;
    }
    return false;
}

void Character::setxDirection(Character::xDirections newDirection) {
    if (xDirection != newDirection) {
        xDirection = newDirection;
        currentSprite.scale(-1.f, 1.f);
    }
}

Character Character::Goblin(float xPosition, float yPosition, Level *currentLevel) {
    Character goblin;
    goblin.level = currentLevel;
    goblin.health = 100;
    goblin.speed = 100;
    Anim idle, walk;
    std::string pathToIdle = "../resources/Animations/Goblin/goblin_idle_anim_f";
    std::string pathToWalk = "../resources/Animations/Goblin/goblin_run_anim_f";
    idle.load(pathToIdle, 4);
    walk.load(pathToWalk, 4);
    goblin.animations[States::IDLE] = idle;
    goblin.animations[States::WALK] = walk;
    goblin.setCurrentState(States::IDLE);
    goblin.updateSprite(1.f / 60);
    float xOrigin = (float)goblin.currentSprite.getTexture()->getSize().x / 2;
    float yOrigin = (float)goblin.currentSprite.getTexture()->getSize().y / 2;
    goblin.currentSprite.setOrigin(sf::Vector2f(xOrigin, yOrigin));
    goblin.currentSprite.setPosition(xPosition, yPosition);
    return goblin;
}



