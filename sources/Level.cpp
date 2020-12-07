//
// Created by sevendart on 26.11.20.
//

#include "../include/Level.h"
#include "../include/Character.h"
#include "../include/Game.h"

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

Level::Level() {
}

 Level Level::mainMenu() {
     Level menu;
     menu.levelName = "menu";
     menu.height = 15;
     menu.width = 10;
     menu.tileSize.x = 200;
     menu.tileSize.y = 200;
     menu.startPosition.y = 600.f;
     menu.startPosition.x = 800.f;
     menu.buttons.push_back(Button::createButton(670,390,"play"));
     menu.buttons.push_back(Button::createButton(600,540,"options2"));
     menu.buttons.push_back(Button::createButton(670,690,"quit"));
     for(Button& button : menu.buttons){
         button.sprite.setColor(sf::Color::Yellow);
     }
     menu.buttons[0].actionPlay = [](int &currentLevel){
         currentLevel = 1;
     };
     menu.buttons[2].actionQuit = [](sf::RenderWindow* window){
         delete window;
     };
     return menu;
 }
