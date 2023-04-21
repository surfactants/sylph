#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

class World : public sf::Drawable {
public:
    World();

    void eraseCell(unsigned int i = 0);

private:
    std::vector<sf::ConvexShape> cells;
    std::vector<sf::RectangleShape> sites;

    sf::RectangleShape frame;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
