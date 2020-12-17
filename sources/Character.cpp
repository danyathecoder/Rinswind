//
// Created by sevendart on 25.11.20.
//

#include "../include/Level.h"
#include "../include/Character.h"
#include <cmath>
#include <iostream>

void Character::updateSprite(float elapsedTime) {
    sprite.setTexture(animations[state].nextFrame(elapsedTime));
    if (state == States::HIT && animations[state].isFinished) state = States::IDLE;
}


void Character::moveCharacter(float x, float y) {
    sf::Vector2f nextPosition(sprite.getPosition().x + x * speed, sprite.getPosition().y + y * speed);
    if (!checkCollisions(sprite.getPosition(), nextPosition))
        this->sprite.move(x * speed, y * speed);
    else {
        sprite.move(-1.f / 10 * x * speed, -1.f / 10 * y * speed);
    }
}

void Character::setCurrentState(Character::States newState) {
    if (newState != state) animations[newState].reset();
    state = newState;
}

bool Character::checkCollisions(sf::Vector2f previousPosition, sf::Vector2f nextPosition) {
    int xDir = (nextPosition.x > previousPosition.x) ? 1 : (nextPosition.x < previousPosition.x)? -1 : 0;
    int yDir = (nextPosition.y > previousPosition.y) ? 1 : (nextPosition.y < previousPosition.y)? -1 : 0;
    sf::Vector2u selfSize = sprite.getTexture()->getSize();
    sf::Vector2f nextLUP = nextPosition;
    nextPosition.x += (xDir * (float)selfSize.x / 2);
    if (yDir > 0) nextPosition.y += (yDir * (float)selfSize.y / 2);

    int** levelMap = level->levelMap.getLevelMap();
    sf::Vector2i mapPos((int)floor(previousPosition.x / 16), (int)floor(previousPosition.y / 16));
    sf::Vector2i nextMapPos((int)floor(nextPosition.x / 16), (int)floor(nextPosition.y / 16));

    int xInc = (xDir != 0)? xDir : 1;
    int yInc = (yDir != 0)? yDir : 1;
    for (int i = mapPos.x; i * xInc <= nextMapPos.x * xInc; i += xInc) {
        for (int j = mapPos.y; j * yInc <= nextMapPos.y * yInc; j += yInc) {
            if (isSolid(levelMap[j][i], level->levelMap.getSolidTiles())) return true;
        }
    }
    nextLUP.x -= ((float)selfSize.x / 2);
    nextLUP.y -= ((float)selfSize.y / 2);
    for (auto &character: level->characters) {
        if (character.get() == this) continue;
        sf::Vector2u charSize = character->sprite.getTexture()->getSize() /*+ sf::Vector2u(12, 12)*/;
        sf::Vector2f charLUP = character->sprite.getPosition();
        charLUP.x -= ((float)charSize.x / 2);
        charLUP.y -= ((float)charSize.y / 2);
        if (isContains(nextLUP, selfSize, this->padding, charSize, charLUP, character->padding)) {
            character->getCollision(this);
            this->getCollision(character.get());
            return true;
        }
    }
    return false;
}

bool Character::isContains(sf::Vector2f firstLUP, sf::Vector2u firstSize, sf::Vector2f firstPadding,
                      sf::Vector2u secondSize, sf::Vector2f secondLUP, sf::Vector2f secondPadding) {
    sf::Vector2f firstCoord[2][2], secondCoord[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            firstCoord[i][j] = firstLUP + sf::Vector2f(firstSize.x * i, firstSize.y * j);
            secondCoord[i][j] = secondLUP + sf::Vector2f(secondSize.x * i, secondSize.y * j);
            firstCoord[i][j] += sf::Vector2f(firstPadding.x * firstSize.x * pow(-1, i), firstPadding.y * firstSize.y * pow(-1, j));
            secondCoord[i][j] += sf::Vector2f(secondPadding.x * secondSize.x * pow(-1, i), secondPadding.y * secondSize.y * pow(-1, j));
        }
    }
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (firstCoord[i][j].x > secondCoord[0][0].x && firstCoord[i][j].x < secondCoord[1][1].x) {
                if (firstCoord[i][j].y > secondCoord[0][0].y && firstCoord[i][j].y < secondCoord[1][1].y)
                    return true;
            }

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (secondCoord[i][j].x > firstCoord[0][0].x && secondCoord[i][j].x < firstCoord[1][1].x)
                if (secondCoord[i][j].y > firstCoord[0][0].y && secondCoord[i][j].y < firstCoord[1][1].y)
                    return true;
    return false;
}

void Character::getCollision(Character* collisionObject) {
    std::cout << "collision Object :" << collisionObject->name << "\n";
    collisionObject->getDamage(0);
    //collisionObject->moveCharacter(0.01f, 0.01f);
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
        sprite.scale(-1.f, 1.f);
    }
}


void Character::getDamage(int damage) {
    if (isImmune) return;
    else {
        health -= damage;
        if (health <= 0) {
            removeFromList();
        }
        isImmune = true;
        sprite.setColor(sf::Color(255, 0, 0, 255));
        setCurrentState(States::HIT);
    }
}

void Character::update(float elapsedTime) {
    updateSprite(elapsedTime);
}

void Character::updateWeapon(float elapsedTime) {
    weapon->updateSprite(elapsedTime);
}

void Character::setPosition(sf::Vector2f position) {
    sprite.setPosition(position);
    weapon->sprite.setPosition(position + sf::Vector2f(0, 10));
}

void Character::checkImpacts(float elapsedTime) {
    if (isImmune) {
        immuneTime += elapsedTime;
        if (immuneTime > immuneDuration) {
            immuneTime = 0;
            isImmune = false;
            sprite.setColor(sf::Color(255, 255, 255, 255));
        }
    }
}

void Character::removeFromList() {
    for (auto it = level->characters.begin(); it != level->characters.end(); it++)
        if (it->get() == this) {
            level->characters.erase(it);
            return;
        }
}

Character::~Character() {

}


