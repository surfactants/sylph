#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include <game/system/entity_manager.hpp>
#include <game/system/component_manager.hpp>

#include <game/system/solar_system.hpp>
#include <game/system/tile_system.hpp>
#include <game/system/system_manager.hpp>

#include <game/data/new_game_data.hpp>

class World {
public:
    World(New_Game_Data data
        , Component_Manager& components
        , Entity_Manager& entities
        , System_Manager& systems);

    Collision_Rect getFrame();

private:
    New_Game_Data data;

    Component_Manager& components;
    Entity_Manager& entities;
    System_Manager& systems;

    sf::Vector2f min;
    sf::Vector2f max;

    Collision_Rect frame;

    void generateSystems();
    void makeSystem(Entity system);
    Entity makeStar(Entity system);
    void makePlanets(Entity system, Entity star);
};
