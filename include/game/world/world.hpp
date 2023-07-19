#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include <game/core/ecs_core.hpp>

#include <game/core/system_manager.hpp>

#include <game/data/new_game_data.hpp>

class World {
public:
    World(New_Game_Data data, ECS_Core* core);

    Collision_Rect getFrame();

private:
    New_Game_Data data;

    ECS_Core* core;

    sf::Vector2f min;
    sf::Vector2f max;

    Collision_Rect frame;
};
