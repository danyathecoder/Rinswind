//
// Created by sevendart on 26.11.20.
//

#include "../include/Level.h"
#include "../include/Character.h"
#include "../include/Button.h"
#include "../include/Goblin.h"

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
    /*for(int i = 50; i < 200; i += 10){
        level.characters.push_back(std::shared_ptr<Character>(new Goblin(i, 40)));
    }*/

    level.characters.push_back(std::shared_ptr<Character>(new Goblin(100, 40)));
    static sf::SoundBuffer buffer;
    buffer.loadFromFile("../resources/levelSound.wav");
    level.soundtrack.setBuffer(buffer);
    level.soundtrack.setLoop(true);

    return level;
}

Level Level::options() {
    Level options;
    options.type = Types::MENU;
    options.levelName = "menu";
    options.height = 15;
    options.width = 10;
    options.tileSize.x = 200;
    options.tileSize.y = 200;

    options.buttons.push_back(Button::createButton(50,450,"back"));



//    options.buttons.push_back(Button::createButton(300,100,"volume"));

    options.buttons[0].action = [](Game *game){
        game->setCurrentLevel(0);
    };

    return options;
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
         game->setCurrentLevel(2);
     };
     menu.buttons[1].action = [](Game *game){
         game->setCurrentLevel(1);
     };
     menu.buttons[2].action = [](Game *game) {
         delete game;
         exit(0);
     };
     return menu;
 }
