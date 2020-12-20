//
// Created by sevendart on 10.12.20.
//

#include "../include/Sword.h"

Sword::Sword() {
    damage = 1;
    angle = 90;
    Animation attack, wait;
    wait.speed = 5;
    std::string waitAnimationPath = "../resources/Animations/Weapons/Sword/weapon_regular_sword_wait";
    std::string attackAnimationPath = "../resources/Animations/Weapons/Sword/weapon_regular_sword_attack";
    attack.load(attackAnimationPath, 2);
    wait.load(waitAnimationPath, 4);
    animations[States::WAIT] = wait;
    animations[States::ATTACK] = attack;
    setCurrentState(States::WAIT);
    updateSprite(1.f / 60);
    sprite.setOrigin(sprite.getLocalBounds().width * 0.5f, sprite.getLocalBounds().height * 0.8f);
    sprite.setScale(0.85f, 0.85f);
    padding = sf::Vector2f(0.1f, 0.1f);
}

void Sword::attack() {
    setCurrentState(States::ATTACK);
}

void Sword::update(float elapsedTime) {
    Weapon::update(elapsedTime);
}
