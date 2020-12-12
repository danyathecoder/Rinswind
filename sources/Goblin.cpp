//
// Created by sevendart on 7.12.20.
//

#include "../include/Goblin.h"
#include "../include/Player.h"
#include "../include/Game.h"

Goblin::Goblin(float xPosition, float yPosition) {
    health = 5;
    speed = 10;
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
    follow(isAggressive(Game::player.currentSprite.getPosition().x, Game::player.currentSprite.getPosition().y, 100.0));
    updateSprite(elapsedTime);
}

void Goblin::follow(bool angry) {
    if (angry) {
        moveCharacter((Game::player.currentSprite.getPosition().x - this->currentSprite.getPosition().x)/400,
                      (Game::player.currentSprite.getPosition().y - this->currentSprite.getPosition().y)/400);
    }
}