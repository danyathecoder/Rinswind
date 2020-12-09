//
// Created by sevendart on 25.11.20.
//

#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#include <SFML/Graphics.hpp>
#include "Anim.h"
#include "Level.h"
#include <map>
#include <vector>
#include <functional>

class Character{
public:
    enum class States{IDLE, WALK, ATTACK, HIT};
    enum class xDirections{LEFT, RIGHT};
    sf::Sprite currentSprite;
    int health;
    float speed;
    Level *level;
    std::string name;
    std::map<States, Anim> animations;
    void setCurrentState(States newState);
    void updateSprite(float elapsedTime);
    virtual void moveCharacter(float x, float y);
    virtual void update(float elapsedTime);
protected:
    States currentState;
    xDirections xDirection = xDirections::RIGHT;
    static bool isSolid(int tile, const std::vector<int> &solidTiles);
    bool checkCollisions(sf::Vector2f previousPosition, sf::Vector2f nextPosition);
    virtual void getCollision(Character* collisionObject);
    static bool isContains(sf::Vector2f firstLUP, sf::Vector2u firstSize, sf::Vector2f firstPadding,
                           sf::Vector2u secondSize, sf::Vector2f secondLUP, sf::Vector2f secondPadding);

public:
    sf::Vector2f padding;
    virtual ~Character();
    void getDamage(int damage);
    void setxDirection(xDirections newDirection);
};

#endif //GAME_CHARACTER_H
