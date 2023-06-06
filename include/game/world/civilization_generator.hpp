#pragma once

#include <game/core/ecs_core.hpp>

#include <game/data/new_game_data.hpp>

#include <game/core/entity_manager.hpp>
#include <game/core/component_manager.hpp>
#include <game/core/system_manager.hpp>

class Civilization_Generator {
public:
    Civilization_Generator(New_Game_Data data, ECS_Core* core);

private:
    New_Game_Data data;

    ECS_Core* core;

    //Component_Manager& components;
    //Entity_Manager& entities;
    //System_Manager& systems;

    void generatePlayer();
    void generateAI();

    void print(Entity civilization);
};
