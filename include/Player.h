//
// Created by sevendart on 26.11.20.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "Character.h"
#include "Sword.h"

class Player: public Character {
private:
    void setKnight();
    void setMage();
    void input(float elapsedTime);
    void keyboard(float elapsedTime);
    void mouse(float elapsedTime);
    virtual void updateWeapon(float elapsedTime) override;
public:
    sf::View camera;
    enum class Classes{KNIGHT, MAGE};
    void update(float elapsedTime) override;
    void moveCharacter(float x, float y) override;
    void setClass(Classes newClass);
    virtual void getCollision(Character* collisionObject) override;
    void setWeaponRotation();
};

#endif //GAME_PLAYER_H
