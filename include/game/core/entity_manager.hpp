#pragma once

#include <array>
#include <memory>
#include <queue>

#include <game/core/entity.hpp>

class Entity_Manager {
public:
    Entity_Manager();

    Entity create() [[nodiscard]];
    void destroy(Entity e);
    void define(Entity e, Signature s);
    void reset();
    Signature signature(Entity e);

    void readAvailable();

private:
    std::queue<Entity> available;
    std::array<Signature, MAX_ENTITIES> signatures {};
};
