//
// Created by sevendart on 10.12.20.
//

#include "../include/Sword.h"
#include "../include/Game.h"
#include <cmath>

Sword::Sword() {
    damage = 10;
    speed = 10;
    angle = 90;
    Animation hit, wait;
    std::string animationPath = "../resources/Animations/Weapons/Sword/weapon_regular_sword";
    hit.load(animationPath, 1);
    wait.load(animationPath, 1);
    animations[States::WAIT] = wait;
    animations[States::ATTACK] = hit;
    setCurrentState(States::WAIT);
    updateSprite(1.f / 60);
    sprite.setOrigin(5, 15);
    sprite.setScale(0.75f, 0.75f);
}

void Sword::attack() {

}

void Sword::rotate() {
    sf::Vector2f mousePos = Game::window->mapPixelToCoords(sf::Mouse::getPosition(Game::window[0]));
    sf::Vector2f viewPos = Game::window->getView().getCenter();
    sf::Vector2f pos = sprite.getPosition();
    sf::Vector2f coords;
    coords.x = mousePos.x - pos.x;
    coords.y = (mousePos.y - pos.y);
    angle = (float)(atan(coords.y / coords.x) * 180 / M_PI);
    if (coords.x < 0)
        angle += 180;
    if (angle < 0) angle += 360;
    Weapon::rotate();
}
