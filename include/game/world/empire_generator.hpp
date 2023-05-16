#pragma once

#include <game/data/new_game_data.hpp>

#include <game/system/entity_manager.hpp>
#include <game/system/component_manager.hpp>
#include <game/system/system_manager.hpp>

class Empire_Generator {
public:
    Empire_Generator(New_Game_Data data
        , Component_Manager& components
        , Entity_Manager& entities
        , System_Manager& systems);

private:
    New_Game_Data data;

    Component_Manager& components;
    Entity_Manager& entities;
    System_Manager& systems;

    void generatePlayer();
    void generateAI();

    void print(Entity empire);
};
