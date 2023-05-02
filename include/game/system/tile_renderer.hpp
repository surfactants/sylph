#pragma once

#include <SFML/Graphics.hpp>

#include <engine/resources/palette.hpp>

#include <game/component/polygon_tile.hpp>
#include <game/component/transform.hpp>

#include "system.hpp"

class Tile_Renderer : public System, public sf::Drawable {
public:
    Tile_Renderer() = default;

    void addTile(Entity e)
    {
        entities.insert(e);
        auto tile = getComponent<Polygon_Tile>(e);
        const size_t n = tile.vertices.size();
        tiles.push_back(sf::ConvexShape(n));
        for (size_t i = 0; i < n; i++) {
            tiles.back().setPoint(i, tile.vertices[i]);
        }
        tiles.back().setFillColor(sf::Color::Transparent);
        tiles.back().setOutlineColor(Palette::white);
        tiles.back().setOutlineThickness(1.f);

        auto transform = getComponent<Transform>(e);
        const static sf::Vector2f size(16.f, 16.f);
        sites.push_back(sf::RectangleShape(size));
        sites.back().setPosition(transform.position);
        sites.back().setOrigin(size / 2.f);
        sites.back().setFillColor(Palette::green);
    }

private:
    std::vector<sf::ConvexShape> tiles;
    std::vector<sf::RectangleShape> sites;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (const auto& t : tiles) {
            target.draw(t, states);
        }
        for (const auto& s : sites) {
            target.draw(s, states);
        }
    }
};
