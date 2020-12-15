//
// Created by sevendart on 25.11.20.
//

#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Level.h"
#include <map>
#include <vector>
#include <functional>
#include "Weapon.h"

class Character{
public:
    enum class States{IDLE, WALK, ATTACK, HIT};
    enum class xDirections{LEFT, RIGHT};
    sf::Sprite currentSprite;
    Weapon *weapon;
    int health;
    float speed;
    Level *level;
    std::string name;
    std::map<States, Animation> animations;
    void setPosition(sf::Vector2f position);
    void setCurrentState(States newState);
    virtual void moveCharacter(float x, float y);
    virtual void update(float elapsedTime);
protected:
    States currentState;
    xDirections xDirection = xDirections::RIGHT;
    float immuneTime; // time pasted since last damage
    float immuneDuration; // immunity duration, unchangeable
    bool isImmune;
    virtual void checkImpacts(float elapsedTime);
    void updateSprite(float elapsedTime);
    virtual void updateWeapon(float elapsedTime);
    static bool isSolid(int tile, const std::vector<int> &solidTiles);
    bool checkCollisions(sf::Vector2f previousPosition, sf::Vector2f nextPosition);
    virtual void getCollision(Character* collisionObject);
    static bool isContains(sf::Vector2f firstLUP, sf::Vector2u firstSize, sf::Vector2f firstPadding,
                           sf::Vector2u secondSize, sf::Vector2f secondLUP, sf::Vector2f secondPadding);

public:
    sf::Vector2f padding;
    virtual ~Character();
    virtual void getDamage(int damage);
    void setxDirection(xDirections newDirection);
};

#endif //GAME_CHARACTER_H
