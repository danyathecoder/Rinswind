//
// Created by danilapoddubny on 19/10/2020.
//

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include <ctime>
#include <cstdlib>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class State {
private:
    std::vector<sf::Texture> textures;
public:
    State();
    virtual ~State();

    virtual void update() = 0;
    virtual void render() = 0;
};


#endif //GAME_STATE_H
