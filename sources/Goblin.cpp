//
// Created by sevendart on 7.12.20.
//

#include "../include/Goblin.h"
#include "../include/Game.h"
#include <cmath>

Goblin::Goblin(float xPosition, float yPosition) {
    health = 2;
    speed = 10;
    Animation idle, walk, hit;
    hit.speed = 5;
    range = 100;
    std::string pathToIdle = "../resources/Animations/Goblin/goblin_idle_anim_f";
    std::string pathToWalk = "../resources/Animations/Goblin/goblin_run_anim_f";
    std::string pathToHit = "../resources/Animations/Goblin/goblin_hit_anim_f";
    idle.load(pathToIdle, 4);
    walk.load(pathToWalk, 4);
    hit.load(pathToHit, 1);
    animations[States::IDLE] = idle;
    animations[States::HIT] = hit;
    animations[States::WALK] = walk;
    animations[States::ATTACK] = walk;
    state = States::IDLE;
    updateSprite(1.f / 60);
    float xOrigin = (float)sprite.getTexture()->getSize().x / 2;
    float yOrigin = (float)sprite.getTexture()->getSize().y / 2;
    sprite.setOrigin(sf::Vector2f(xOrigin, yOrigin));
    sprite.setPosition(xPosition, yPosition);
    padding = sf::Vector2f(0.49f, 0.49f);
    name = "goblin";
    weapon = new Weapon();
    weapon->ownership = Weapon::Own::ENEMY;
    immuneDuration = 0.1f;
    immuneTime = 0;
    isImmune = false;
}

Goblin::~Goblin() = default;

void Goblin::update(float elapsedTime) {
    checkImpacts(elapsedTime);
    checkStates();
    actionSwitcher();
    updateSprite(elapsedTime);
}

void Goblin::getCollision(Character *collisionObject) {
    sf::Vector2f coords = (sprite.getPosition() - collisionObject->sprite.getPosition());
    float angle = (float)(atan(coords.y / coords.x) * 180 / M_PI);
    if (coords.x < 0)
        angle += 180;
    if (angle < 0) angle += 360;
    //sf::Vector2f revDir(cos(angle) * 0.1f,sin(angle) * 0.1f);
    if (collisionObject->name == "Knight") {
        collisionObject->getDamage(1);
    }
}
