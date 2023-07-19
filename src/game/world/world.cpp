#include <game/world/world.hpp>

#include <cassert>

#include <engine/math/collide.hpp>
#include <engine/math/prng.hpp>

#include <game/world/gen/voronoi/diagram.hpp>

World::World(New_Game_Data data, ECS_Core* core)
    : data { data }
    , core { core }
{}

Collision_Rect World::getFrame()
{
    return frame;
}
