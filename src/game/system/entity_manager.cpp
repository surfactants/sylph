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
    entities[e] = s;
}

Signature Entity_Manager::signature(Entity e)
{
    return entities[e];
}

void Entity_Manager::destroy(Entity e)
{
    entities[e].reset();
    available.push(e);
}
