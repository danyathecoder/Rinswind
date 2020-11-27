//
// Created by sevendart on 25.11.20.
//

#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#include <SFML/Graphics.hpp>
#include "Anim.h"
#include <map>

class Character/*: public sf::Drawable, public sf::Transformable*/{
public:
    enum class States{IDLE, WALK, ATTACK, HIT};
    States getCurrentState() const;
    void setCurrentState(States newState);
    void updateSprite(float elapsedTime);
    virtual void moveCharacter(float x, float y);
    sf::Sprite currentSprite;
    int health;
    float speed;
    std::map<States, Anim> animations;
protected:
    States currentState;
};

#endif //GAME_CHARACTER_H
