//
// Created by sevendart on 7.12.20.
//

#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H

#include "Character.h"

class Enemy : public Character {
protected:
    virtual void idle();
    virtual void attack();
    virtual void walk();
    virtual void hit();
    float range;
    virtual void actionSwitcher();
    virtual void update(float elapsedTime) override;
public:
    void checkStates();
};

#endif //GAME_ENEMY_H
