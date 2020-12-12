//
// Created by sevendart on 7.12.20.
//

#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H

#include "Character.h"

class Enemy : public Character {
    //virtual void idle();
    //virtual void attack();
    //virtual void walk();
    //virtual void hit();
    //virtual void getCollision(Character *collisionObject) override;
    virtual void update(float elapsedTime) override;
    virtual void follow(bool angry);
public:
    bool isAggressive(float playerSpriteX, float playerSpriteY, float range);
};

#endif //GAME_ENEMY_H
