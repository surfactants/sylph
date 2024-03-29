#pragma once

#include <functional>
#include <set>

#include <game/core/components.hpp>
#include <game/core/entity.hpp>

class System {
public:
    std::set<Entity> entities;

    template <typename T>
    static inline std::function<T(Entity)> getComponent;

    std::string name;
};
