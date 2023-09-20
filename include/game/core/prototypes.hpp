#pragma once

#include <map>

#include "entity_manager.hpp"
#include "component_manager.hpp"

class Prototypes {
public:
    Prototypes(Entity_Manager& entities, Component_Manager& components);

private:
    Entity_Manager& entities;
    Component_Manager& components;
};
