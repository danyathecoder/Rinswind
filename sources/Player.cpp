//
// Created by sevendart on 26.11.20.
//

#include "../include/Player.h"

void Player::moveCharacter(float x, float y) {
    sf::Vector2f nextPosition(currentSprite.getPosition().x + x * speed, currentSprite.getPosition().y + y * speed);
    if (!checkCollisions(currentSprite.getPosition(), nextPosition)) {
        this->currentSprite.move(x * speed, y * speed);
        camera.move(x * speed, y * speed);
        weapon->sprite.move(x * speed, y * speed);
    }
    else {
        this->currentSprite.move(x * speed * -1 / 2, y * speed * -1 / 2);
        camera.move(x * speed * -1 / 2, y * speed * -1 / 2);
        weapon->sprite.move(x * speed * -1 / 2, y * speed * -1 / 2);
    }
}

void Player::setClass(Classes newClass) {
    switch (newClass) {
        case Classes::KNIGHT:
            setKnight();
            break;
        case Classes::MAGE:
            setMage();
            break;
    }
}

void Player::setKnight() {
    this->health = 100;
    this->speed = 100;
    this->name = "Knight";
    Animation idle, walk, hit;
    std::string pathToIdle = "../resources/Animations/Knight/knight_m_idle_anim_f";
    std::string pathToWalk = "../resources/Animations/Knight/knight_m_run_anim_f";
    std::string pathToHit = "../resources/Animations/Knight/knight_m_hit_anim_f";
    hit.load(pathToHit, 1);
    idle.load(pathToIdle, 4);
    walk.load(pathToWalk, 4);
    this->animations[States::IDLE] = idle;
    this->animations[States::WALK] = walk;
    this->animations[States::HIT] = hit;
    setCurrentState(States::IDLE);
    updateSprite(1.f / 60);
    currentSprite.setOrigin(8, 14);
    padding = sf::Vector2f(0.f, 0.f);
    weapon = new Sword();
}

void Player::setMage() {

}

void Player::update(float elapsedTime) {
    updateSprite(elapsedTime);
    updateWeapon(elapsedTime);
}

void Player::updateWeapon(float elapsedTime) {
    weapon->updateSprite(elapsedTime);
}

