//
// Created by sevendart on 7.12.20.
//

#ifndef GAME_GOBLIN_H
#define GAME_GOBLIN_H

#include "Enemy.h"
#include "Player.h"



class Goblin : public Enemy {
public:
    Goblin(float xPosition, float yPosition);
    ~Goblin();
    virtual void update(float elapsedTime) override;
    virtual void follow(bool angry) override;

};

#endif //GAME_GOBLIN_H
