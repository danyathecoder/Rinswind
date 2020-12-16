//
// Created by sevendart on 10.12.20.
//

#include "../include/Weapon.h"
#include "../include/Game.h"
#include <iostream>
#include <cmath>

void Weapon::updateSprite(float elapsedTime) {
       sprite.setTexture(animations[currentState].nextFrame(elapsedTime));
    if (currentState == States::ATTACK && animations[currentState].isFinished) setCurrentState(States::WAIT);
    rotate();
}

void Weapon::setCurrentState(Weapon::States newState) {
    if (newState != currentState) {
        animations[newState].reset();
        if (newState == States::ATTACK) attacking = true;
        else attacking = false;
    }
    currentState = newState;
}

void Weapon::attack() {

}

void Weapon::rotate() {
    sprite.setRotation(90 + angle);
}

Weapon::~Weapon() = default;


bool Weapon::checkCollisions() {
    sf::Vector2u selfSize = sprite.getTexture()->getSize();
    sf::Vector2f LUP = sprite.getPosition() - sprite.getOrigin();
    for (auto &character: Game::currentGame->getCurrentLevel()->characters) {
        if (ownership == Own::PLAYER && character->name == "Knight") continue;
        if (ownership != Own::PLAYER && character->name != "Knight") continue;
        sf::Vector2u charSize = character->sprite.getTexture()->getSize();
        sf::Vector2f charLUP = character->sprite.getPosition();
        charLUP.x -= ((float)charSize.x / 2);
        charLUP.y -= ((float)charSize.y / 2);
        if (isContains(LUP, selfSize, this->padding, charSize, charLUP, sf::Vector2f(-0.5f,-0.5f))) {
            character->getDamage(this->damage);
            return true;
        }
    }
    return false;
}

bool Weapon::isContains(sf::Vector2f firstLUP, sf::Vector2u firstSize, sf::Vector2f firstPadding,
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

void Weapon::update(float elapsedTime) {
    if (attacking)
        checkCollisions();
    updateSprite(elapsedTime);
}
