//
// Created by sevendart on 7.12.20.
//

#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H

#include "Character.h"

class Enemy : public Character {
protected:
    virtual void idle(float elapsedTime);
    virtual void attack(float elapsedTime);
    virtual void walk(float elapsedTime);
    virtual void hit(float elapsedTime);
    float range;
    virtual void actionSwitcher(float elapsedTime);
    virtual void update(float elapsedTime) override;
public:
    void checkStates();
};

#endif //GAME_ENEMY_H
