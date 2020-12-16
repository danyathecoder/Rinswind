//
// Created by sevendart on 26.11.20.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "Character.h"
#include "Sword.h"
#include "UserInterface.h"

class Player: public Character {
private:
    void setKnight();
    void setMage();
    void input(float elapsedTime);
    void keyboard(float elapsedTime);
    void mouse(float elapsedTime);
    void updateWeapon(float elapsedTime) override;
public:
    sf::View camera;
    UserInterface UI;
    enum class Classes{KNIGHT, MAGE};
    void update(float elapsedTime) override;
    void moveCharacter(float x, float y) override;
    void setClass(Classes newClass);
    void getCollision(Character* collisionObject) override;
    void setWeaponRotation();
    virtual void getDamage(int damage) override;
};

#endif //GAME_PLAYER_H
