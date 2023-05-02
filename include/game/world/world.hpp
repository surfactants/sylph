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
    World(New_Game_Data data) : data { data } {}

    std::vector<std::pair<Transform, Polygon_Tile>> polygonTiles();
    std::vector<std::pair<sf::Vector2f, Tile>> tiles();

    Collision_Rect getFrame();

private:
    New_Game_Data data;

    sf::Vector2f min;
    sf::Vector2f max;

    Collision_Rect frame;
};
