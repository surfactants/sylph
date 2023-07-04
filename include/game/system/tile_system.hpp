#pragma once

#include <SFML/Graphics.hpp>

#include <engine/resources/palette.hpp>
#include <engine/input/double_click.hpp>

#include "system.hpp"

class Tile_System : public System, public sf::Drawable {
    //typedef std::tuple<sf::ConvexShape, sf::CircleShape, Entity> Tile;

public:
    Tile_System();

    void update(const sf::Vector2f& mpos);

    void addTile(Entity e);

    void activate();
    void deactivate();

    void repaintTile(Entity e);

    std::function<void(Entity)> activateUI;
    std::function<void(Entity)> switchContext;

    Entity random();

    void loadEntity(Entity e);
    void setTileVisible(Entity e);
    void setSiteVisible(Entity e);

    Entity active { NULL_ENTITY };
    Entity moused { NULL_ENTITY };

private:
    //std::vector<Tile> tiles;
    std::vector<sf::ConvexShape> tiles;
    std::vector<sf::CircleShape> sites;

    sf::ConvexShape moused_frame;
    sf::ConvexShape active_frame;

    std::vector<sf::VertexArray> lines;

    std::map<Entity, size_t> entity_to_site;
    std::map<size_t, Entity> site_to_entity;

    std::map<Entity, size_t> entity_to_tile;
    std::map<size_t, Entity> tile_to_entity;

    std::map<size_t, int> site_to_tile;
    std::map<size_t, int> tile_to_site;


    //std::map<Entity, size_t> entity_to_index;
    //std::map<size_t, Entity> index_to_entity;

    constexpr static float moused_border { 4.f };
    constexpr static float active_border { 8.f };

    Double_Click double_click;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
