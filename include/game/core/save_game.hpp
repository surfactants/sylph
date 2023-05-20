#pragma once

#include <game/system/component_manager.hpp>
#include <game/system/entity_manager.hpp>
#include <game/system/system_manager.hpp>

class Save_Game {
public:
    Save_Game(Component_Manager& components
            , Entity_Manager& entities
            , System_Manager& systems);

private:
    Component_Manager& components;
    Entity_Manager& entities;
    System_Manager& systems;
};
