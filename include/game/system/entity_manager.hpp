#pragma once

#include <array>
#include <memory>
#include <queue>

#include <game/entity/entity.hpp>

class Entity_Manager {
public:
    Entity_Manager();

    constexpr static Entity MAX_ENTITIES { 10000 };

    Entity create();
    void define(Entity e, Signature s);
    Signature signature(Entity e);
    void destroy(Entity e);

private:
    std::queue<Entity> available;
    std::array<Signature, MAX_ENTITIES> entities;
};
