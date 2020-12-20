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
    for(int i = 50; i < 200; i += 20){
        level.characters.push_back(std::shared_ptr<Character>(new Goblin(i, 60)));
    }
    //level.characters.push_back(std::shared_ptr<Character>(new Goblin(80, 80)));
    static sf::SoundBuffer buffer;
    buffer.loadFromFile("../resources/levelSound.wav");
    level.soundtrack.setBuffer(buffer);
    level.soundtrack.setLoop(true);

    return level;
}

Level Level::firstLevel() {
    Level level;
    level.levelName = "level2";
    level.height = 23;
    level.width = 64;
    level.tileSize.x = level.tileSize.y = 16;
    level.startPosition.x = 64.f;
    level.startPosition.y = 64.f;
    level.levelMap.setSolidTiles({28,14,36,2});
    level.type = Types::LEVEL;
    level.resetLevelCharacters();
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

    options.buttons[0].idleColor = sf::Color::Yellow;
    options.buttons[0].activateColor = sf::Color::Red;

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
     menu.buttons.push_back(Button::createButton(50,400,"quit"));

     for(Button& button : menu.buttons){
         button.activateColor = sf::Color::Red;
         button.idleColor = sf::Color::Yellow;
     }
     menu.buttons[0].action = [](Game *game) {
         game->initPlayer();
         game->setCurrentLevel(2);
     };

     menu.buttons[1].action = [](Game *game) {
         delete game;
         exit(0);
     };
     return menu;
 }

 Level Level::deathScreen() {
    Level deathScreen;
    deathScreen.type = Types::MENU;
    deathScreen.levelName = "deathscreen";
    deathScreen.width = 4;
    deathScreen.height = 4;
    deathScreen.tileSize = sf::Vector2u(1000,1000);

    deathScreen.buttons.push_back(Button::createButton(160, 50, "buttons/you_died"));
    deathScreen.buttons.push_back(Button::createButton(150, 300, "buttons/try_again"));
    deathScreen.buttons.push_back(Button::createButton(120, 400, "buttons/to_main"));

    for (auto& button: deathScreen.buttons) {
        button.sprite.setColor(sf::Color(255, 255, 255, 255));
    }
    deathScreen.buttons[0].activateColor = sf::Color(255,255,255);
    deathScreen.buttons[1].activateColor = sf::Color::White;
    deathScreen.buttons[2].activateColor = sf::Color::White;
    deathScreen.buttons[0].idleColor = sf::Color(255,255,255);
    deathScreen.buttons[1].idleColor = sf::Color::Yellow;
    deathScreen.buttons[2].idleColor = sf::Color::Yellow;

    deathScreen.buttons[0].action = [](Game *game) {};

    deathScreen.buttons[1].action = [](Game* game) {
        game->resetLevel(2);
        game->setCurrentLevel(2);
    };

    deathScreen.buttons[2].action = [](Game* game) {
        game->resetLevel(2);
        Game::currentGame->camera = new sf::View(sf::FloatRect(0, 0, 800, 600));
        game->setCurrentLevel(0);
    };
     return deathScreen;
}

void Level::resetLevelCharacters() {
    characters.clear();
    characters.push_back(std::shared_ptr<Character>(new Goblin(120.f, 312.f)));
    characters.push_back(std::shared_ptr<Character>(new Goblin(138.f, 312.f)));
    characters.push_back(std::shared_ptr<Character>(new Goblin(150.f, 312.f)));

    characters.push_back(std::shared_ptr<Character>(new Goblin(520.f, 250.f)));
    characters.push_back(std::shared_ptr<Character>(new Goblin(520.f, 265.f)));
    characters.push_back(std::shared_ptr<Character>(new Goblin(520.f, 280.f)));
    characters.push_back(std::shared_ptr<Character>(new Goblin(520.f, 228.f)));
}

Level Level::winScreen() {
    Level winScreen;
    winScreen.type = Types::MENU;
    winScreen.levelName = "deathscreen";
    winScreen.width = 4;
    winScreen.height = 4;
    winScreen.tileSize = sf::Vector2u(1000, 1000);

    winScreen.buttons.push_back(Button::createButton(120, 50, "buttons/you_win"));
    winScreen.buttons.push_back(Button::createButton(150, 300, "buttons/try_again"));
    winScreen.buttons.push_back(Button::createButton(120, 400, "buttons/to_main"));

    for (auto& button: winScreen.buttons) {
        button.sprite.setColor(sf::Color(255, 255, 255, 255));
    }
    winScreen.buttons[0].activateColor = sf::Color(255, 255, 255);
    winScreen.buttons[1].activateColor = sf::Color::White;
    winScreen.buttons[2].activateColor = sf::Color::White;
    winScreen.buttons[0].idleColor = sf::Color(255, 255, 255);
    winScreen.buttons[1].idleColor = sf::Color::Yellow;
    winScreen.buttons[2].idleColor = sf::Color::Yellow;

    winScreen.buttons[0].action = [](Game *game) {};

    winScreen.buttons[1].action = [](Game* game) {
        game->resetLevel(2);
        game->setCurrentLevel(2);
    };

    winScreen.buttons[2].action = [](Game* game) {
        game->resetLevel(2);
        Game::currentGame->camera = new sf::View(sf::FloatRect(0, 0, 800, 600));
        game->setCurrentLevel(0);
    };
    return winScreen;
}