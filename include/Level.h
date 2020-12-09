//
// Created by sevendart on 25.11.20.
//

#include "TileMap.h"

#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

class Character;
class Button;

class Level {
private:
    sf::Vector2u tileSize;
    int width, height;
    std::string levelName;
    sf::Vector2f startPosition;
public:
    enum class Types {LEVEL, MENU};
    Level();
    Types type;
    sf::Vector2f getStartPosition() const;
    std::vector<Character> characters;
    std::vector<Button> buttons;
    TileMap levelMap;
    void loadLevel();
    static Level zeroLevel();
    static Level mainMenu();
};





#endif //GAME_LEVEL_H
