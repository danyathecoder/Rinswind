#include "../include/Game.h"
#include <string>
#include "../include/Anim.h"
#include "../include/Button.h"
//static functions

//init functions

void Game::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "");
    window->setFramerateLimit(60);
    camera = new sf::View();
    camera->reset(sf::FloatRect (0, 0, 800, 600));
}

//constructors/destructors

Game::Game() {
    currentLevel = 0;
    initWindow();
    levels.push_back(Level::mainMenu());
    levels.push_back(Level::zeroLevel());
    this->loadLevel(currentLevel);
}

Game::~Game() {
    delete this->window;
}

//functions
void Game::render() {
    this->window->clear();
    this->window->setView(*camera);

    window->draw(levels[currentLevel].levelMap);

    for (auto &character: levels[currentLevel].characters) {
        this->window->draw(character.currentSprite);
    }

    for (auto &button: levels[currentLevel].buttons) {
        //button.sprite.setColor(sf::Color::Yellow);
        button.setTexture();
        this->window->draw(button.sprite);
    }

    if (levels[currentLevel].type != Level::Types::MENU) window->draw(player.currentSprite);

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
    if (levels[currentLevel].type != Level::Types::MENU) player.update(dt);
    for (Character &character: levels[currentLevel].characters)
        character.update(dt);
}

void Game::updateSFMLEvents() {
    while (this->window->pollEvent(this->event)) {
        if (this->event.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::input(float dt) {
    if (levels[currentLevel].type != Level::Types::MENU) keyboard(dt);
    if (levels[currentLevel].type != Level::Types::LEVEL) mouse();
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
    camera = &player.camera;
}

void Game::keyboard(float dt) {
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

void Game::mouse() {
    for (auto &button: levels[currentLevel].buttons) {
        sf::IntRect buttonRect = button.sprite.getTextureRect();
        sf::Vector2f position = button.sprite.getPosition();
        buttonRect.left = position.x;
        buttonRect.top = position.y;
        if (buttonRect.contains(sf::Mouse::getPosition(window[0]))) {
            button.sprite.setColor(sf::Color::Red);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                button.action(this);
        }
        else {
            button.sprite.setColor(sf::Color::Yellow);
        }
    }
}

void Game::setCurrentLevel(int level) {
    currentLevel = level;
    loadLevel(level);
}

