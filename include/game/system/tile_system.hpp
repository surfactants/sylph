#pragma once

#include <SFML/Graphics.hpp>

#include <engine/resources/palette.hpp>

#include <game/component/polygon_tile.hpp>
#include <game/component/transform.hpp>

#include "system.hpp"

class Tile_System : public System, public sf::Drawable {
public:
    Tile_System() = default;

    void update(const sf::Vector2f& mpos);

    void addTile(Entity e);

private:
    sf::ConvexShape* moused;
    sf::ConvexShape moused_frame;
    std::vector<sf::ConvexShape> tiles;
    std::vector<sf::CircleShape> sites;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
