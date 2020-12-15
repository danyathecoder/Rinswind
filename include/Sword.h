//
// Created by sevendart on 10.12.20.
//

#ifndef GAME_SWORD_H
#define GAME_SWORD_H

#include "Weapon.h"

class Sword: public Weapon {
    virtual void attack() override;
public:
    Sword();
    virtual void update(float elapsedTime) override;
};


#endif //GAME_SWORD_H
