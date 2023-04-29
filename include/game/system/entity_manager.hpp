#pragma once

#include <array>
#include <memory>
#include <queue>

#include <game/entity/entity.hpp>

class Entity_Manager {
public:
    Entity_Manager();

    Entity create();
    void destroy(Entity e);
    void define(Entity e, Signature s);
    void reset();

private:
    std::queue<Entity> available;
    std::array<Signature, MAX_ENTITIES> signatures;
};
