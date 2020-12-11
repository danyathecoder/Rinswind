#include "../include/Game.h"
#include <string>
#include "../include/Animation.h"
#include "../include/Button.h"


void Game::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "");
    Game::window->setFramerateLimit(60);
    camera = new sf::View();
    camera->reset(sf::FloatRect (0, 0, 800, 600));
}


Game::Game() {
    currentLevel = 0;
    initWindow();
    levels.push_back(Level::mainMenu());
    levels.push_back(Level::zeroLevel());
    this->loadLevel(currentLevel);
}

//functions
void Game::render() {
    Game::window->clear();
    Game::window->setView(*camera);

    window->draw(levels[currentLevel].levelMap);

    for (auto &character: levels[currentLevel].characters) {
        Game::window->draw(character->currentSprite);
        Game::window->draw(character->weapon->sprite);
    }

    for (auto &button: levels[currentLevel].buttons) {
        button.setTexture();
        Game::window->draw(button.sprite);
    }


    Game::window->display();
}

void Game::run() {
        while (Game::window->isOpen()) {
            this->update();
            this->render();
        }
}

void Game::update() {
    float dt = dtClock.restart().asSeconds();
    this->input(dt);
    this->updateSFMLEvents();
    //if (levels[currentLevel].type != Level::Types::MENU) player.update(dt);
    for (auto &character: levels[currentLevel].characters)
        character->update(dt);
}

void Game::updateSFMLEvents() {
    while (Game::window->pollEvent(this->event)) {
        if (this->event.type == sf::Event::Closed)
            Game::window->close();
    }
}

void Game::input(float dt) {
    if (levels[currentLevel].type != Level::Types::MENU) keyboard(dt);
    if (levels[currentLevel].type != Level::Types::LEVEL) mouse();
}

void Game::loadLevel(int number) {
    currentLevel = number;
    levels[currentLevel].loadLevel();
    if (levels[currentLevel].type != Level::Types::MENU) {
        player.level = &levels[currentLevel];
        player.setPosition(levels[currentLevel].getStartPosition());
        player.camera.setCenter(player.currentSprite.getPosition());
        player.setCurrentState(Character::States::IDLE);
        for (auto &character: levels[currentLevel].characters)
            character->level = &levels[currentLevel];
        levels[currentLevel].characters.push_back(std::shared_ptr<Character>(&player));
    }
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

Game::~Game() = default;

