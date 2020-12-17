//
// Created by sevendart on 26.11.20.
//

#include "../include/Player.h"
#include "../include/Game.h"
#include <cmath>

void Player::moveCharacter(float x, float y) {
    sf::Vector2f nextPosition(sprite.getPosition().x + x * speed, sprite.getPosition().y + y * speed);
    if (!checkCollisions(sprite.getPosition(), nextPosition)) {
        this->sprite.move(x * speed, y * speed);
        camera.move(x * speed, y * speed);
        weapon->sprite.move(x * speed, y * speed);
    }
    else {
        this->sprite.move(x * speed * -1 / 10, y * speed * -1 / 10);
        camera.move(x * speed * -1 / 10, y * speed * -1 / 10);
        weapon->sprite.move(x * speed * -1 / 10, y * speed * -1 / 10);
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
    this->health = 3;
    this->speed = 100;
    this->name = "Knight";
    Animation idle, walk, hit;
    walk.speed = idle.speed = hit.speed = 5;
    hit.speed = 1;
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
    sprite.setOrigin(8, 14);
    padding = sf::Vector2f(0.f, 0.f);
    weapon = new Sword();
    weapon->ownership = Weapon::Own::PLAYER;
    immuneDuration = 0.75f;
    immuneTime = 0;
    isImmune = false;
    UI = UserInterface();
}

void Player::setMage() {

}

void Player::keyboard(float elapsedTime) {
    bool isInMove = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        moveCharacter(-1 * elapsedTime, 0);
        setCurrentState(Character::States::WALK);
        setxDirection(Character::xDirections::LEFT);
        isInMove = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        moveCharacter(1 * elapsedTime, 0);
        setCurrentState(Character::States::WALK);
        setxDirection(Character::xDirections::RIGHT);
        isInMove = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        moveCharacter(0, -1 * elapsedTime);
        setCurrentState(Character::States::WALK);
        isInMove = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        moveCharacter(0, 1 * elapsedTime);
        setCurrentState(Character::States::WALK);
        isInMove = true;
    }
    if (!isInMove) {
        if (state != States::HIT) setCurrentState(Character::States::IDLE);
    }
}

void Player::mouse(float elapsedTime) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        weapon->attack();
}

void Player::input(float elapsedTime) {
    keyboard(elapsedTime);
    mouse(elapsedTime);
}

void Player::update(float elapsedTime) {
    input(elapsedTime);
    checkImpacts(elapsedTime);
    updateWeapon(elapsedTime);
    updateSprite(elapsedTime);
    UI.update();
}

void Player::setWeaponRotation() {
    sf::Vector2f mousePos = Game::window->mapPixelToCoords(sf::Mouse::getPosition(Game::window[0]));
    sf::Vector2f pos = weapon->sprite.getPosition();
    sf::Vector2f coords;
    coords.x = mousePos.x - pos.x;
    coords.y = (mousePos.y - pos.y);
    weapon->angle = (float)(atan(coords.y / coords.x) * 180 / M_PI);
    if (coords.x < 0)
        weapon->angle += 180;
    if (weapon->angle < 0) weapon->angle += 360;
}

void Player::updateWeapon(float elapsedTime) {
    setWeaponRotation();
    weapon->update(elapsedTime);
}

void Player::getCollision(Character *collisionObject) {

}

void Player::getDamage(int damage) {
    if (isImmune) return;
    else {
        health -= damage;
        if (health <= 0) {
            Game::currentGame->getCurrentLevel()->soundtrack.stop();
            Game::currentGame->loadLevel(3);
            Game::currentGame->camera = new sf::View(sf::FloatRect(0, 0, 800, 600));
        }
        isImmune = true;
        sprite.setColor(sf::Color(255, 0, 0, 255));
        setCurrentState(States::HIT);
    }
    UI.update();
}

Player::~Player() = default;




