//
// Created by sevendart on 26.11.20.
//

#include "../include/Level.h"
#include "../include/Character.h"

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
    level.height = 16;
    level.width = 24;
    level.tileSize.x = level.tileSize.y = 16;
    level.startPosition.x = 160.f;
    level.startPosition.y = 160.f;
    level.levelMap.setSolidTiles({28,14,36,2});
    level.characters.push_back(Character::Goblin(80.f, 80.f));
    return level;
}

// <<<<<<< sevendart
Level::Level() {

// =======
// //level "menu"
// Level Level::mainMenu(){
//     Level level;
//     level.levelName = "menu";
//     level.height = 15;
//     level.width = 10;
//     level.tileSize.x = 200;
//     level.tileSize.y = 200;
//     level.startPosition.x = 800.f;
//     level.startPosition.y = 600.f;
//     return level;
// >>>>>>> danyathecoder
}
