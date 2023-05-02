#include <game/system/entity_manager.hpp>

#include <cassert>

Entity_Manager::Entity_Manager()
{
    for (Entity e = 0; e < MAX_ENTITIES; e++) {
        available.push(e);
    }
}

Entity Entity_Manager::create()
{
    assert(available.size() > 0 && "Entity limit reached in ::create!");
    Entity e = available.front();
    available.pop();
    return e;
}

void Entity_Manager::define(Entity e, Signature s)
{
    assert(e < MAX_ENTITIES && "Entity out of range in ::define!");
    signatures[e] = s;
}

void Entity_Manager::destroy(Entity e)
{
    assert(e < MAX_ENTITIES && "Entity out of range in ::destroy!");
    signatures[e].reset();
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

Signature Entity_Manager::signature(Entity e)
{
    assert(e < MAX_ENTITIES && "Entity out of range in ::get!");
    return signatures[e];
}
