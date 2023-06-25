#pragma once

#include <vector>

#include <game/core/entity.hpp>

struct Hierarchy {
    std::vector<Entity> children;
    std::vector<Entity> parents;
    std::vector<Entity> neighbors;
};
