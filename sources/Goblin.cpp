//
// Created by sevendart on 7.12.20.
//

#include "../include/Goblin.h"

Goblin::Goblin(float xPosition, float yPosition) {
    health = 5;
    speed = 100;
    Animation idle, walk, hit;
    hit.speed = 5;
    std::string pathToIdle = "../resources/Animations/Goblin/goblin_idle_anim_f";
    std::string pathToWalk = "../resources/Animations/Goblin/goblin_run_anim_f";
    std::string pathToHit = "../resources/Animations/Goblin/goblin_hit_anim_f";
    idle.load(pathToIdle, 4);
    walk.load(pathToWalk, 4);
    hit.load(pathToHit, 1);
    animations[States::IDLE] = idle;
    animations[States::HIT] = hit;
    animations[States::WALK] = walk;
    currentState = States::IDLE;
    updateSprite(1.f / 60);
    float xOrigin = (float)currentSprite.getTexture()->getSize().x / 2;
    float yOrigin = (float)currentSprite.getTexture()->getSize().y / 2;
    currentSprite.setOrigin(sf::Vector2f(xOrigin, yOrigin));
    currentSprite.setPosition(xPosition, yPosition);
    padding = sf::Vector2f(0.49f, 0.49f);
    name = "goblin";
    weapon = new Weapon();
}

Goblin::~Goblin() {

}

void Goblin::update(float elapsedTime) {
    printf("FUCK");
    updateSprite(elapsedTime);
    moveCharacter(elapsedTime, 0);
}
