#include <game/system/entity_manager.hpp>

Entity_Manager::Entity_Manager()
{
    for (Entity e = 0; e < MAX_ENTITIES; e++) {
        available.push(e);
    }
}

Entity Entity_Manager::create()
{
    Entity e = available.front();
    available.pop();
    return e;
}

void Entity_Manager::define(Entity e, Signature s)
{
    signatures[e] = s;
}

void Entity_Manager::destroy(Entity e)
{
    available.push(e);
}

void Entity_Manager::reset()
{
    available = {}; // clears queue
    for (Entity e = 0; e < MAX_ENTITIES; e++) {
        available.push(e);
    }
    signatures = std::array<Signature, MAX_ENTITIES>();
}
