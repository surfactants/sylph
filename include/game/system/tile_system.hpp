#pragma once

#include <SFML/Graphics.hpp>

#include <engine/resources/palette.hpp>
#include <engine/util/double_click.hpp>

#include "system.hpp"

class Tile_System : public System, public sf::Drawable {
    typedef std::tuple<sf::ConvexShape, sf::CircleShape, Entity> Tile;

public:
    Tile_System() = default;

    void update(const sf::Vector2f& mpos);

    void addTile(Entity e);

    void activate();
    void deactivate();

    void repaintTile(Entity e);

    std::function<void(Entity)> activateUI;
    std::function<void(Entity)> switchContext;

    Tile* active;

    Entity random();

private:
    std::vector<Tile> tiles;
    Tile* moused;
    sf::ConvexShape moused_frame;
    sf::ConvexShape active_frame;

    std::map<Entity, size_t> entity_to_index;
    std::map<size_t, Entity> index_to_entity;

    constexpr static float moused_border { 4.f };
    constexpr static float active_border { 8.f };

    Double_Click double_click;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
