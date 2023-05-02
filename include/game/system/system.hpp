#pragma once

#include <functional>
#include <set>

#include <game/entity/entity.hpp>

class System {
public:
    std::set<Entity> entities;

    template <typename T>
    static inline std::function<T(Entity)> getComponent;
};
