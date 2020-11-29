//
// Created by sevendart on 25.11.20.
//

#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#include <SFML/Graphics.hpp>
#include "Anim.h"
#include <map>
#include "Level.h"
#include <vector>

class Character{
public:
    enum class States{IDLE, WALK, ATTACK, HIT};
    States getCurrentState() const;
    void setCurrentState(States newState);
    void updateSprite(float elapsedTime);
    virtual void moveCharacter(float x, float y);
    sf::Sprite currentSprite;
    int health;
    float speed;
    enum class xDirections{LEFT, RIGHT};
    enum class yDirections{UP, DOWN};
    Level *level;
    std::map<States, Anim> animations;
protected:
    static bool isSolid(int tile, const std::vector<int> &solidTiles);
    bool checkCollisions(sf::Vector2f previousPosition, sf::Vector2f nextPosition);
    void getCollision(Character& collisionObject);
    std::vector<Character*> *characters;
    States currentState;
    xDirections xDirection = xDirections::RIGHT;
    yDirections yDirection = yDirections::UP;
public:
    void setyDirection(yDirections newDirection);
    void setxDirection(xDirections newDirection);
};

#endif //GAME_CHARACTER_H
