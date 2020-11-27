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

    //printf("%d %d\n", player.currentSprite.getTexture()->getSize().x, player.currentSprite.getTexture()->getSize().y);
    this->window->draw(player.currentSprite);

    for (const auto & character : characters)
        this->window->draw(character.currentSprite);

    //render items

    this->window->display();
}

void Game::run() {
    while (this->window->isOpen()) {
        this->input();
        this->updateDt();
        this->update();
        this->render();
    }
}

void Game::update() {
    this->updateSFMLEvents();
    player.updateSprite(0.01f);
    for (auto & character : characters)
        character.updateSprite(0.01f);
}

void Game::updateSFMLEvents() {
    while (this->window->pollEvent(this->event)) {
        if (this->event.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::updateDt() {
    //time, which took to render and update one frame
    this->dt = this->dtClock.restart().asSeconds();
    //std::system("clear");//"cls" for windows
    //std::cout << this->dt << std::endl;
}

void Game::input() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player.moveCharacter(-1, 0);
        player.setCurrentState(Character::States::WALK);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player.moveCharacter(1, 0);
        player.setCurrentState(Character::States::WALK);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player.moveCharacter(0, -1);
        player.setCurrentState(Character::States::WALK);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player.moveCharacter(0, 1);
        player.setCurrentState(Character::States::WALK);
    }
    else {
        player.setCurrentState(Character::States::IDLE);
    }
}

void Game::loadLevel(int number) {
    currentLevel = levelList[number];
    currentLevel.loadLevel();
    player.currentSprite.setPosition(currentLevel.getStartPosition());
    player.camera.setCenter(player.currentSprite.getPosition());
    player.setCurrentState(Character::States::IDLE);
}

void Game::initPlayer() {
    player.setClass(Player::Classes::KNIGHT);

    player.camera.setSize(400, 300);
    player.setCurrentState(Character::States::IDLE);
    //characters.push_back(player);
    window->setView(player.camera);
}
