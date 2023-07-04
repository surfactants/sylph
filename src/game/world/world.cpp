#include <game/world/world.hpp>

#include <cassert>

#include <engine/math/collide.hpp>
#include <engine/math/prng.hpp>

#include <game/world/gen/voronoi/diagram.hpp>

World::World(New_Game_Data data, ECS_Core* core)
    : data { data }
    , core { core }
{
    generateSystems();
}

Collision_Rect World::getFrame()
{
    return frame;
}

void World::generateSystems()
{
    size_t point_upper_bound;
    size_t point_lower_bound;

    float size_factor;

    min = sf::Vector2f(0.f, 0.f);

    switch (data.size) {
        case New_Game_Data::SMALL:
            point_lower_bound = 150;
            point_upper_bound = 250;
            size_factor = 8.f;
            break;
        case New_Game_Data::MEDIUM:
            point_lower_bound = 350;
            point_upper_bound = 450;
            size_factor = 12.f;
            break;
        case New_Game_Data::LARGE: // * 8
            point_lower_bound = 550;
            point_upper_bound = 650;
            size_factor = 16.f;
            break;
        case New_Game_Data::VERY_LARGE: // * 8
            point_lower_bound = 750;
            point_upper_bound = 850;
            size_factor = 20.f;
            break;
    }

    max = sf::Vector2f(1920.f, 1080.f);
    max *= size_factor;

    size_t point_count = prng::number(point_lower_bound, point_upper_bound);
    sf::Vector2<double> world_min(min);
    sf::Vector2<double> world_max(max);

    Voronoi::Diagram d(point_count, world_min, world_max);
    std::vector<sf::ConvexShape> cells = d.get();
    std::vector<sf::Vector2f> sites = d.sites();
    std::vector<std::vector<size_t>> neighbors = d.neighbors();
    std::vector<Entity> systems;

    size_t n = cells.size();

    for (size_t i = 0; i < n; i++) {
        systems.push_back(core->entities.create());
    }

    for (size_t i = 0; i < n; i++) {
        // make systems
        Transform transform;
        transform.position = sites[i];
        Polygon_Tile tile;
        size_t p = cells[i].getPointCount();
        for (size_t j = 0; j < p; j++) {
            tile.vertices.push_back(cells[i].getPoint(j));
        }

        Signature s;

        s.set(toInt(Component::BODY_INFO));
        s.set(toInt(Component::POLYGON_TILE));
        s.set(toInt(Component::TRANSFORM));
        s.set(toInt(Component::HIERARCHY));
        s.set(toInt(Component::COLLISION_RECT));
        s.set(toInt(Component::RESOURCE));
        s.set(toInt(Component::ENTITY_DATA));

        Entity system = systems[i];
        core->entities.define(system, s);

        core->components.addComponent(system, tile);
        core->components.addComponent(system, transform);

        Hierarchy hierarchy;

        for (const auto& neighbor : neighbors[i]) {
            hierarchy.neighbors.push_back(neighbor);
        }

        system_generator.make(system, hierarchy);
    }

    for (const auto& system : systems) {
        core->systems.tile_system.loadEntity(system);
    }

    min -= sf::Vector2f(512.f, 512.f);
    max += sf::Vector2f(512.f, 512.f);

    frame.setPosition(sf::Vector2f(min));
    frame.setSize(sf::Vector2f(max - min));
}
