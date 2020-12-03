//
// Created by sevendart on 26.11.20.
//

#include "../include/Player.h"

void Player::moveCharacter(float x, float y) {
    sf::Vector2f dir;
    dir.x = (float)currentSprite.getTexture()->getSize().x / 2;
    if (x < 0) dir.x *= -1;
    dir.y = (float)currentSprite.getTexture()->getSize().y / 2;
    if (y < 0) dir.y *= 0;
    sf::Vector2f nextPosition(currentSprite.getPosition().x + x * speed + dir.x, currentSprite.getPosition().y + y * speed + dir.y);
    if (!checkCollisions(currentSprite.getPosition(), nextPosition)) {
        this->currentSprite.move(x * speed, y * speed);
        camera.move(x * speed, y * speed);
    }
    else {
        this->currentSprite.move(x * speed * -1 / 2, y * speed * -1 / 2);
        camera.move(x * speed * -1 / 2, y * speed * -1 / 2);
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
    Anim idle, walk;
    std::string pathToIdle = "../resources/Animations/Knight/knight_m_idle_anim_f";
    std::string pathToWalk = "../resources/Animations/Knight/knight_m_run_anim_f";
    idle.load(pathToIdle, 4);
    walk.load(pathToWalk, 4);
    this->animations[States::IDLE] = idle;
    this->animations[States::WALK] = walk;
    currentSprite.setOrigin(8, 14);
}

void Player::setMage() {

}

