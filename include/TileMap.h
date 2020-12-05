#include <SFML/Graphics.hpp>

#ifndef GAMERPG_TILEMAP_H
#define GAMERPG_TILEMAP_H

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    bool load(const std::string &tileset, sf::Vector2u tileSize, const std::string &level, unsigned int width, unsigned int height);
    int ** getLevelMap();
    const std::vector<int> &getSolidTiles();
    TileMap();
    void setSolidTiles(std::vector<int> tiles);
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    static int **loadLevel(const std::string &level, unsigned int width, unsigned int height);
    std::vector<int> solidTiles;
    unsigned int width, height;
    int **levelMap;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

#endif //GAMERPG_TILEMAP_H
