//
// Created by sevendart on 26.11.20.
//

#include "../include/Level.h"

void Level::loadLevel() {
    levelMap.load("../resources/" + levelName + ".png", tileSize, "../resources/" + levelName + ".txt", width, height);
}

sf::Vector2f Level::getStartPosition() const {
    sf::Vector2f position(startPosition.x, startPosition.y);
    return position;
}

Level Level::zeroLevel() {
    Level level;
    level.levelName = "level";
    level.height = 14;
    level.width = 22;
    level.tileSize.x = level.tileSize.y = 16;
    level.startPosition.x = 160.f;
    level.startPosition.y = 160.f;
    return level;
}

//level "menu"
Level Level::mainMenu(){
    Level level;
    level.levelName = "menu";
    level.height = 15;
    level.width = 10;
    level.tileSize.x = 200;
    level.tileSize.y = 200;
    level.startPosition.x = 800.f;
    level.startPosition.y = 600.f;
    return level;
}
