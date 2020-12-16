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
    sf::Vector2f playerPosition = Game::player.sprite.getPosition();
    sf::Vector2f position = sprite.getPosition();
    if (pow((playerPosition.x - position.x),2) + pow((playerPosition.y - position.y),2) <= pow(range, 2)) {
        setCurrentState(States::ATTACK);
    }
    else {
        setCurrentState(Character::States::IDLE);
    }
}

void Enemy::attack() {
    sf::Vector2f coords = (sprite.getPosition() - Game::player.sprite.getPosition());
    float angle = std::atan(coords.y / coords.x);
    if (coords.x > 0)
        angle += M_PI;
    sf::Vector2f direction(std::cos(angle) * 0.1f, std::sin(angle) * 0.1f);
    moveCharacter(direction.x, direction.y);
}

void Enemy::actionSwitcher() {
    switch (state) {
        case States::ATTACK:
            attack();
        case States::IDLE:
            idle();
        case States::WALK:
            walk();
        case States::HIT:
            hit();
    }
}

void Enemy::idle() {

}

void Enemy::walk() {

}

void Enemy::hit() {

}
