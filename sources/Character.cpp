//
// Created by sevendart on 25.11.20.
//

#include "../include/Level.h"
#include "../include/Character.h"
#include <cmath>
#include <iostream>

void Character::updateSprite(float elapsedTime) {
    currentSprite.setTexture(animations[currentState].nextFrame(elapsedTime));
    if (currentState == States::HIT && animations[currentState].isFinished) currentState = States::IDLE;
}


Character::States Character::getCurrentState() const {
    return currentState;
}

void Character::moveCharacter(float x, float y) {
    sf::Vector2f nextPosition(currentSprite.getPosition().x + x * speed, currentSprite.getPosition().y + y * speed);
    if (!checkCollisions(currentSprite.getPosition(), nextPosition))
        this->currentSprite.move(x * speed, y * speed);
    else {
        currentSprite.move(-1 * x * speed / 2, -1 * y * speed / 2);
    }
}

void Character::setCurrentState(Character::States newState) {
    if (newState != currentState) animations[newState].reset();
    currentState = newState;
}

bool Character::checkCollisions(sf::Vector2f previousPosition, sf::Vector2f nextPosition) {
    int xDir = (nextPosition.x > previousPosition.x) ? 1 : (nextPosition.x < previousPosition.x)? -1 : 0;
    int yDir = (nextPosition.y > previousPosition.y) ? 1 : (nextPosition.y < previousPosition.y)? -1 : 0;
    sf::Vector2u selfSize = currentSprite.getTexture()->getSize();
    sf::Vector2f nextLUP = nextPosition;
    nextPosition.x += (xDir * (float)selfSize.x / 2);
    if (yDir > 0) nextPosition.y += (yDir * (float)selfSize.y / 2);

    int** levelMap = level->levelMap.getLevelMap();
    sf::Vector2i mapPos((int)floor(previousPosition.x / 16), (int)floor(previousPosition.y / 16));
    sf::Vector2i nextMapPos((int)floor(nextPosition.x / 16), (int)floor(nextPosition.y / 16));

    int xInc = (xDir != 0)? xDir : 1;
    int yInc = (yDir != 0)? yDir : 1;
    for (int i = mapPos.x; i * xInc <= nextMapPos.x * xInc; i += xInc) {
        for (int j = mapPos.y; j * yInc <= nextMapPos.y * yInc; j += yInc) {
            if (isSolid(levelMap[j][i], level->levelMap.getSolidTiles())) return true;
        }
    }
    nextLUP.x -= ((float)selfSize.x / 2);
    nextLUP.y -= ((float)selfSize.y / 2);
    for (auto &character: level->characters) {
        sf::Vector2u charSize = character.currentSprite.getTexture()->getSize() /*+ sf::Vector2u(12, 12)*/;
        sf::Vector2f charLUP = character.currentSprite.getPosition();
        charLUP.x -= ((float)charSize.x / 2);
        charLUP.y -= ((float)charSize.y / 2);
        if (isContains(nextLUP, selfSize, this->padding, charSize, charLUP, character.padding)) {
            character.getCollision(this);
            this->getCollision(&character);
            return true;
        }
    }
    return false;
}

bool Character::isContains(sf::Vector2f firstLUP, sf::Vector2u firstSize, sf::Vector2f firstPadding,
                      sf::Vector2u secondSize, sf::Vector2f secondLUP, sf::Vector2f secondPadding) {
    //printf("%f %f\n", secondPadding.x * (float)secondSize.x, secondPadding.y * (float)secondSize.y);
    sf::Vector2f firstCoord[2][2], secondCoord[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            firstCoord[i][j] = firstLUP + sf::Vector2f(firstSize.x * i, firstSize.y * j);
            secondCoord[i][j] = secondLUP + sf::Vector2f(secondSize.x * i, secondSize.y * j);
            firstCoord[i][j] += sf::Vector2f(firstPadding.x * firstSize.x * pow(-1, i), firstPadding.y * firstSize.y * pow(-1, j));
            secondCoord[i][j] += sf::Vector2f(secondPadding.x * secondSize.x * pow(-1, i), secondPadding.y * secondSize.y * pow(-1, j));
        }
    }
    //std::swap(secondCoord[0][1], secondCoord[1][0]);
    //std::swap(firstCoord[0][1], firstCoord[1][0]);
    /*printf("\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            printf("%f %f ", secondCoord[i][j].x, secondCoord[i][j].y);
        printf("\n");
    }*/
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (firstCoord[i][j].x > secondCoord[0][0].x && firstCoord[i][j].x < secondCoord[1][1].x) {
                //printf("%f < %f < %f\n", secondCoord[0][0].x, firstCoord[i][j].x, secondCoord[1][0].x);
                if (firstCoord[i][j].y > secondCoord[0][0].y && firstCoord[i][j].y < secondCoord[1][1].y)
                    return true;
            }

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (secondCoord[i][j].x > firstCoord[0][0].x && secondCoord[i][j].x < firstCoord[1][0].x)
                if (secondCoord[i][j].y > firstCoord[0][0].y && secondCoord[i][j].y < firstCoord[1][1].y)
                    return true;
    return false;
}

void Character::getCollision(Character* collisionObject) {
    std::cout << "collision Object :" << collisionObject->name << "\n";
    collisionObject->getDamage(0);
}

bool Character::isSolid(int tile, const std::vector<int> &solidTiles) {
    for (int current: solidTiles) {
        if (current == tile) return true;
    }
    return false;
}

void Character::setxDirection(Character::xDirections newDirection) {
    if (xDirection != newDirection) {
        xDirection = newDirection;
        currentSprite.scale(-1.f, 1.f);
    }
}

Character Character::Goblin(float xPosition, float yPosition) {
    Character goblin;
    goblin.health = 100;
    goblin.speed = 100;
    Anim idle, walk, hit;
    hit.speed = 5;
    std::string pathToIdle = "../resources/Animations/Goblin/goblin_idle_anim_f";
    std::string pathToWalk = "../resources/Animations/Goblin/goblin_run_anim_f";
    std::string pathToHit = "../resources/Animations/Goblin/goblin_hit_anim_f";
    idle.load(pathToIdle, 4);
    walk.load(pathToWalk, 4);
    hit.load(pathToHit, 1);
    goblin.animations[States::HIT] = hit;
    goblin.animations[States::IDLE] = idle;
    goblin.animations[States::WALK] = walk;
    goblin.setCurrentState(States::IDLE);
    goblin.updateSprite(1.f / 60);
    float xOrigin = (float)goblin.currentSprite.getTexture()->getSize().x / 2;
    float yOrigin = (float)goblin.currentSprite.getTexture()->getSize().y / 2;
    goblin.currentSprite.setOrigin(sf::Vector2f(xOrigin, yOrigin));
    goblin.currentSprite.setPosition(xPosition, yPosition);
    goblin.padding = sf::Vector2f(0.49f, 0.49f);
    //goblin.currentSprite.scale(2.f, 2.f);
    goblin.name = "goblin";
    return goblin;
}

void Character::getDamage(int damage) {
    if (health - damage < 0) delete(this);
    else {
        health -= damage;
        setCurrentState(States::HIT);
    }
}



