//
// Created by sevendart on 7.12.20.
//

#include "../include/Enemy.h"
#include "../include/Game.h"
#include <cmath>

void Enemy::update(float elapsedTime) {
    Character::update(elapsedTime);
}

void Enemy::checkStates() {
    sf::Vector2f playerPosition = Game::player->sprite.getPosition();
    sf::Vector2f position = sprite.getPosition();
    if (pow((playerPosition.x - position.x),2) + pow((playerPosition.y - position.y),2) <= pow(range, 2)) {
        setCurrentState(States::ATTACK);
    }
    else {
        setCurrentState(Character::States::IDLE);
    }
}

void Enemy::attack(float elapsedTime) {
    sf::Vector2f coords = (sprite.getPosition() - Game::player->sprite.getPosition());
    float angle = std::atan(coords.y / coords.x);
    if (coords.x > 0)
        angle += M_PI;
    sf::Vector2f direction(std::cos(angle) * elapsedTime, std::sin(angle) * elapsedTime);
    moveCharacter(direction.x, direction.y);
}

void Enemy::actionSwitcher(float elapsedTime) {
    switch (state) {
        case States::ATTACK:
            attack(elapsedTime);
        case States::IDLE:
            idle(elapsedTime);
        case States::WALK:
            walk(elapsedTime);
        case States::HIT:
            hit(elapsedTime);
    }
}

void Enemy::idle(float elapsedTime) {

}

void Enemy::walk(float elapsedTime) {

}

void Enemy::hit(float elapsedTime) {

}
