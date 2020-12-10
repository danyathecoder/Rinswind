//
// Created by sevendart on 10.12.20.
//

#ifndef GAME_SWORD_H
#define GAME_SWORD_H

#include "Weapon.h"

class Sword: public Weapon {
    virtual void attack() override;
    virtual void rotate() override;

public:
    Sword();
};


#endif //GAME_SWORD_H
