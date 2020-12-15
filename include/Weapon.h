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
    enum class Own{PLAYER, ENEMY};
    Own ownership;
    sf::Sprite sprite;
    int damage;
    int speed;
    float angle;
    bool attacking;
    virtual void update(float elapsedTime);
    virtual void attack();
    virtual ~Weapon();
    void setCurrentState(States newState);
    void updateSprite(float elapsedTime);
protected:
    virtual void rotate();
    std::map<States, Animation> animations;
    States currentState;
    sf::Vector2f padding;
    bool checkCollisions();
    bool isContains(sf::Vector2f firstLUP, sf::Vector2u firstSize, sf::Vector2f firstPadding, sf::Vector2u secondSize,
                    sf::Vector2f secondLUP, sf::Vector2f secondPadding);
};


#endif //GAME_WEAPON_H
