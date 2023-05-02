#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include <game/component/collision_rect.hpp>
#include <game/component/polygon_tile.hpp>
#include <game/component/tile.hpp>
#include <game/component/transform.hpp>

#include <game/data/new_game_data.hpp>

class World {
public:
    World(New_Game_Data data);

    void load();

    std::vector<std::pair<Transform, Polygon_Tile>> polygonTiles();
    std::vector<std::pair<sf::Vector2f, Tile>> tiles();

    sf::Vector2f min;
    sf::Vector2f max;

    Collision_Rect getFrame();

private:
    sf::ConvexShape* moused_cell { nullptr };
    sf::ConvexShape* active_cell { nullptr };

    constexpr static float moused_thickness { 2.f };
    constexpr static float active_thickness { 4.f };

    void setMousedCell(sf::ConvexShape* cell);

    New_Game_Data data;

    Collision_Rect frame;
};
