//
// Created by sevendart on 16.12.20.
//

#include "../include/UserInterface.h"
#include "../include/Game.h"

void UserInterface::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &heart;
    target.draw(vertices, states);
}

UserInterface::UserInterface() {
    heart.loadFromFile("../resources/GUI/heart.png");
    vertices.setPrimitiveType(sf::Quads);
    int health = Game::player->health;
    currentHealth = health;
    setHealth(health);
}

void UserInterface::setHealth(int count) {
    vertices.resize(count * 4);
    for (int i = 0; i < count; i++) {
        sf::Vertex *quad = &vertices[i * 4];
        sf::Vector2u tileSize = heart.getSize();
        quad[0].position = sf::Vector2f(i * tileSize.x, 0);
        quad[1].position = sf::Vector2f((i + 1) * tileSize.x,  0);
        quad[2].position = sf::Vector2f((i + 1) * tileSize.x, tileSize.y);
        quad[3].position = sf::Vector2f(i * tileSize.x, tileSize.y);

        quad[0].texCoords = sf::Vector2f(0,0);
        quad[1].texCoords = sf::Vector2f(tileSize.x, 0);
        quad[2].texCoords = sf::Vector2f(tileSize.x, tileSize.y);
        quad[3].texCoords = sf::Vector2f(0, tileSize.y);
    }
}

void UserInterface::update() {
    int health = Game::player->health;
    if (health != currentHealth) {
        setHealth(health);
        currentHealth = health;
    }
    this->setPosition(Game::window->mapPixelToCoords(sf::Vector2i(5, 5)));
}
