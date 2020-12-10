//
// Created by sevendart on 10.12.20.
//

#ifndef GAME_WEAPON_H
#define GAME_WEAPON_H

#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <map>

class Weapon {
public:
    enum class States {ATTACK, WAIT};
    void setCurrentState(States newState);
    void updateSprite(float elapsedTime);
    sf::Sprite sprite;
    int damage;
    int speed;
    float angle;
    virtual void attack();
    virtual ~Weapon();
protected:
    float radius;
    virtual void rotate();
    std::map<States, Animation> animations;
    States currentState;
};


#endif //GAME_WEAPON_H
