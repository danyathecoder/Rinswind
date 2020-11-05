//
// Created by danilapoddubny on 19/10/2020.
//

#include "Game.h"

//static functions

//init functions

void Game::initWindow() {
    this->window = new sf::RenderWindow (sf::VideoMode(800, 800), "Pavsha is (not) faggot!");
}

//constructors/destructors
Game::Game() {
    this->initWindow();
}

Game::~Game() {
    delete this -> window;
}

//functions
void Game::render() {
    this->window->clear();

    //render items

    this->window->display();
}

void Game::run() {
    while (this->window->isOpen()){
        this->updateDt();
        this->update();
        this->render();
        }
}

void Game::update() {
    this->updateSFMLEvents();
}

void Game::updateSFMLEvents() {

        while (this->window->pollEvent(this->event))
        {
            if (this->event.type == sf::Event::Closed)
                this->window->close();
        }

}

void Game::updateDt() {
    //time, which took to render and update one frame
    this->dt = this->dtClock.restart().asSeconds();
    std::system("clear");//"cls" for windows
    std::cout << this->dt << std::endl;

}
