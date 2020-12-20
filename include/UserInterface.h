//
// Created by sevendart on 16.12.20.
//

#ifndef GAME_USERINTERFACE_H
#define GAME_USERINTERFACE_H

#include <SFML/Graphics.hpp>

class UserInterface: public sf::Drawable, public sf::Transformable {
    sf::Texture heart;
    sf::VertexArray vertices;
    int currentHealth;
public:
    void update();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    UserInterface();

    void setHealth(int count);
};


#endif //GAME_USERINTERFACE_H
