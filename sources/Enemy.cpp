//
// Created by sevendart on 7.12.20.
//

#include "../include/Enemy.h"

void Enemy::update(float elapsedTime) {
    Character::update(elapsedTime);
}

bool Enemy::isAggressive(float playerSpriteX, float playerSpriteY, float range){
    bool aggressive = false;
    if((playerSpriteY - this->currentSprite.getPosition().y) * (playerSpriteY - this->currentSprite.getPosition().y) +
       (playerSpriteX - this->currentSprite.getPosition().x) * (playerSpriteX - this->currentSprite.getPosition().x)<= range * range){
        aggressive = true;
    }
    return aggressive;
}

void Enemy::follow(bool angry) {
    moveCharacter(0, 0);
}
