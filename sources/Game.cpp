#include "../include/Game.h"
#include <string>
#include "../include/Anim.h"
//static functions

//init functions

void Game::initWindow() {
    this->window = new sf::RenderWindow (sf::VideoMode(800, 600), "game");
    window->setFramerateLimit(60);
}

//constructors/destructors

Game::Game() {
    this->initWindow();
    this->initPlayer();
    levelList.push_back(Level::zeroLevel());
    this->loadLevel(0);
}

Game::~Game() {
    delete this -> window;
}

//functions
void Game::render() {
    window->setView(player.camera);
    this->window->clear();

    window->draw(currentLevel.levelMap);

    for (auto &character : characters) {
        this->window->draw(character->currentSprite);
    }

    //render items

    this->window->display();
}

void Game::run() {
    while (this->window->isOpen()) {
        this->update();
        this->render();
    }
}

void Game::update() {
    float dt = dtClock.restart().asSeconds();
    this->input(dt);
    this->updateSFMLEvents();
    for (auto & character : characters)
        character->updateSprite(dt);
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
    currentLevel = levelList[number];
    currentLevel.loadLevel();
    player.level = &currentLevel;
    player.currentSprite.setPosition(currentLevel.getStartPosition());
    player.camera.setCenter(player.currentSprite.getPosition());
    player.setCurrentState(Character::States::IDLE);
}

void Game::initPlayer() {
    player.setClass(Player::Classes::KNIGHT);
    player.camera.setSize(400, 300);
    player.setCurrentState(Character::States::IDLE);
    characters.push_back(&player);
    window->setView(player.camera);
}
