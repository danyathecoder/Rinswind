//
// Created by sevendart on 25.11.20.
//

#include "TileMap.h"

#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

class Character;
class Button;

class Level {
public:
    enum class Types {LEVEL, MENU};
    Types type;
    TileMap levelMap;
    std::vector<Character> characters;
    std::vector<Button> buttons;
    Level();
    void loadLevel();
    sf::Vector2f getStartPosition() const;
    static Level zeroLevel();
    static Level mainMenu();
private:
    sf::Vector2u tileSize;
    int width, height;
    std::string levelName;
    sf::Vector2f startPosition;
};





#endif //GAME_LEVEL_H
