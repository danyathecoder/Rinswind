#include "../include/Game.h"
#include <string>
#include "../include/Anim.h"
#include_next "../include/Button.h"
//static functions

//init functions

void Game::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "");
    window->setFramerateLimit(60);
}

//constructors/destructors

Game::Game() {
    currentLevel = 0;
    this->initWindow();
    this->initPlayer();
    levels.push_back(Level::zeroLevel());
    this->loadLevel(0);
}

Game::~Game() {
    delete this -> window;
}

//functions
void Game::render() {
    window->setView(player.camera);
    this->window->clear();

    window->draw(levels[currentLevel].levelMap);


    for (auto &character: levels[currentLevel].characters) {
        this->window->draw(character.currentSprite);
    }

    window->draw(player.currentSprite);

    this->window->display();
}

void Game::run() {
        while (this->window->isOpen()) {
            this->update();
            this->render();
            sf::Mouse mouse;
        }
}

void Game::update() {
    float dt = dtClock.restart().asSeconds();
    this->input(dt);
    this->updateSFMLEvents();
    player.update(dt);
    for (auto &character: levels[currentLevel].characters)
        character.update(dt);
}

void Game::updateSFMLEvents() {
    while (this->window->pollEvent(this->event)) {
        if (this->event.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::input(float dt) {
    bool isInMove = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player.moveCharacter(-1 * dt, 0);
        player.setCurrentState(Character::States::WALK);
        player.setxDirection(Character::xDirections::LEFT);
        isInMove = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player.moveCharacter(1 * dt, 0);
        player.setCurrentState(Character::States::WALK);
        player.setxDirection(Character::xDirections::RIGHT);
        isInMove = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player.moveCharacter(0, -1 * dt);
        player.setCurrentState(Character::States::WALK);
        isInMove = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player.moveCharacter(0, 1 * dt);
        player.setCurrentState(Character::States::WALK);
        isInMove = true;
    }
    if (!isInMove) {
        player.setCurrentState(Character::States::IDLE);
    }
}

void Game::loadLevel(int number) {
    currentLevel = number;
    levels[currentLevel].loadLevel();
    player.level = &levels[currentLevel];
    player.currentSprite.setPosition(levels[currentLevel].getStartPosition());
    player.camera.setCenter(player.currentSprite.getPosition());
    player.setCurrentState(Character::States::IDLE);
    for (auto &character: levels[currentLevel].characters)
        character.level = &levels[currentLevel];
}

void Game::initPlayer() {
    player.setClass(Player::Classes::KNIGHT);
    player.camera.setSize(400, 300);
    player.setCurrentState(Character::States::IDLE);
    window->setView(player.camera);
}


