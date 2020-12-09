//
// Created by sevendart on 26.11.20.
//

#include "../include/Level.h"
#include "../include/Character.h"
#include "../include/Button.h"

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
    level.type = Types::LEVEL;
    return level;
}

Level::Level() {
}

 Level Level::mainMenu() {
     Level menu;
     menu.type = Types::MENU;
     menu.levelName = "menu";
     menu.height = 15;
     menu.width = 10;
     menu.tileSize.x = 200;
     menu.tileSize.y = 200;

     menu.buttons.push_back(Button::createButton(50,100,"play"));
     menu.buttons.push_back(Button::createButton(50,250,"options2"));
     menu.buttons.push_back(Button::createButton(50,400,"quit"));
     for(Button& button : menu.buttons){
         button.sprite.setColor(sf::Color::Yellow);
     }
     menu.buttons[0].action = [](Game *game) {
         game->initPlayer();
         game->setCurrentLevel(1);
     };

     menu.buttons[1].action = [](Game *game){

     };

     menu.buttons[2].action = [](Game *game) {
         delete game;
         exit(0);
     };

     menu.buttons[0].actionPlay = [](int &currentLevel){
         currentLevel = 1;
     };
     /*menu.buttons[2].actionQuit = [](sf::RenderWindow* window){
                 delete window;
                 exit(0);
     };*/
     return menu;
 }
