//
// Created by sevendart on 26.11.20.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "Character.h"

class Player: public Character {
private:
    void setKnight();
    void setMage();
public:
    void update(float elapsedTime) override;
    void moveCharacter(float x, float y) override;
    sf::View camera;
    enum class Classes{
        KNIGHT, MAGE
    };
    void setClass(Classes newClass);
};

#endif //GAME_PLAYER_H
