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
    this->setLevelNumber(0);
    this->initWindow();
    levelList.push_back(Level::mainMenu());
    levelList.push_back(Level::zeroLevel());

    //to avoid generation of hero on menu level
    if(getLevelNumber()){
        this->initPlayer();
    }
    this->loadLevel(getLevelNumber());
}

Game::~Game() {
    delete this -> window;
}

//functions
void Game::render() {
    window->setView(player.camera);
    this->window->clear();

    window->draw(currentLevel.levelMap);

    //to draw buttons
    if(levelNumber == 0) {
        Button button;
        window->draw(button.playButton(window, levelNumber));
    }


    //printf("%d %d\n", player.currentSprite.getTexture()->getSize().x, player.currentSprite.getTexture()->getSize().y);
    //this->window->draw(player.currentSprite);

    for (const auto & character : characters)
        this->window->draw(character->currentSprite);

    //render items

    this->window->display();
}

void Game::run() {
        while (this->window->isOpen()) {
            this->update();
            this->render();
            sf::Mouse mouse;
            std::cout << mouse.getPosition(window[0]).x << " " << mouse.getPosition(window[0]).y << '\n';
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player.moveCharacter(-1 * dt, 0);
        player.setCurrentState(Character::States::WALK);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player.moveCharacter(1 * dt, 0);
        player.setCurrentState(Character::States::WALK);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player.moveCharacter(0, -1 * dt);
        player.setCurrentState(Character::States::WALK);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player.moveCharacter(0, 1 * dt);
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
    characters.push_back(&player);
    window->setView(player.camera);
}

int Game::getLevelNumber() const {
    return levelNumber;
}

void Game::setLevelNumber(int levelNumber) {
    Game::levelNumber = levelNumber;
}
