#pragma once

#include <vector>

#include <game/core/entity.hpp>

struct Hierarchy {
    std::vector<Entity> child;
    std::vector<Entity> parent;
};
