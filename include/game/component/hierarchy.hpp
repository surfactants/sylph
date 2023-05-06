#pragma once

#include <vector>

#include <game/entity/entity.hpp>

struct Hierarchy {
    std::vector<Entity> child;
    std::vector<Entity> parent;
};
