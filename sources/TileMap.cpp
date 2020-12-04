#include "../include/TileMap.h"
#include <fstream>
#include <utility>

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);
}

bool TileMap::load(const std::string &tileset, sf::Vector2u tileSize, const std::string &level, unsigned int width,
                   unsigned int height) {

    if (!m_tileset.loadFromFile(tileset)) {
        return false;
    }

    levelMap = loadLevel(level, width, height);
    if (levelMap == nullptr) {
        return false;
    }

    this->width = width;
    this->height = height;

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    for (unsigned int i = 0; i < width; i++) {
        for (unsigned int j = 0; j < height; j++) {
            int tileNumber = levelMap[j][i];

            int column = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int row = tileNumber / (m_tileset.getSize().x / tileSize.x);

            sf::Vertex *quad = &m_vertices[(i + j * width) * 4];

            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);


            quad[0].texCoords = sf::Vector2f(column * tileSize.x, row * tileSize.y);
            quad[1].texCoords = sf::Vector2f((column + 1) * tileSize.x, row * tileSize.y);
            quad[2].texCoords = sf::Vector2f((column + 1) * tileSize.x, (row + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(column * tileSize.x, (row + 1) * tileSize.y);
        }
    }

    return true;
}

int **TileMap::loadLevel(const std::string &level, unsigned int width, unsigned int height) {
    std::ifstream input(level);
    if (!input.good()) {
        return nullptr;
    }
    int **result = new int*[height];
    for (int i = 0; i < height; i++) {
        result[i] = new int[width];
        for (int j = 0; j < width; j++) {
            input >> result[i][j];
        }
    }
    return result;
}

int** TileMap::getLevelMap() {
    return levelMap;
}

const std::vector<int> &TileMap::getSolidTiles() {
    return solidTiles;
}

TileMap::TileMap() {

}

void TileMap::setSolidTiles(std::vector<int> tiles) {
    solidTiles = std::move(tiles);
}

