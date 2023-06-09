#pragma once

#include "component_manager.hpp"
#include "entity_manager.hpp"
#include "system_manager.hpp"
#include "game_info.hpp"

struct ECS_Core {
    Component_Manager components;
    Entity_Manager entities;
    System_Manager systems;
    Game_Info info;

    ECS_Core() = default;
    ECS_Core(const ECS_Core*) = delete;
    ECS_Core operator = (const ECS_Core*) = delete;
};
