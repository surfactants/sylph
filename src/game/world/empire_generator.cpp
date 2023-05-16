#include <game/world/empire_generator.hpp>

#include <engine/util/prng.hpp>

#include <iostream>

Empire_Generator::Empire_Generator(New_Game_Data data
    , Component_Manager& components
    , Entity_Manager& entities
    , System_Manager& systems)
    : data { data }
    , components { components }
    , entities { entities }
    , systems { systems }
{
    generatePlayerEmpire();
}

void Empire_Generator::generatePlayerEmpire()
{
    Entity empire = entities.create();
    Signature sig;
    sig.flip(toInt(Component::ENTITY_DATA));
    sig.flip(toInt(Component::EMPIRE_DATA));
    entities.define(empire, sig);

    Entity_Data entity_data;
    entity_data.name = data.player_name;
    entity_data.description = "player_empire_desc";

    Entity capital_system = systems.tile_system.random();
    auto children = components.getComponent<Hierarchy>(capital_system).child;
    size_t body_index;
    do {
        body_index = prng::number(children.size());
    } while (body_index == 0 && children.size() != 0);
    Entity homeworld = children[body_index];

    Empire_Data empire_data;
    empire_data.capital_system = capital_system;
    empire_data.homeworld = homeworld;
    empire_data.systems.push_back(capital_system);
    empire_data.color = data.player_color;

    components.addComponent(empire, entity_data);
    components.addComponent(empire, empire_data);

    components.getComponent<Polygon_Tile>(capital_system).color = data.player_color;
    auto& system_info = components.getComponent<Body_Info>(capital_system);
    system_info.owned = true;
    system_info.owner = empire;

    auto& home_info = components.getComponent<Body_Info>(homeworld);
    home_info.owned = true;
    home_info.owner = empire;

    systems.tile_system.repaintTile(capital_system);

    print(empire);
}

void Empire_Generator::print(Entity empire)
{
    auto entity_data = components.getComponent<Entity_Data>(empire);
    auto empire_data = components.getComponent<Empire_Data>(empire);
    std::cout << "generated empire '" << entity_data.name << "' (" << empire << ")\n";
    auto capital_info = components.getComponent<Body_Info>(empire_data.capital_system);
    std::cout << "\tlocated in the " << capital_info.name << " system (" << empire_data.capital_system << ")\n";
    auto homeworld = components.getComponent<Body_Info>(empire_data.homeworld);
    std::cout << "\thomeworld is " << homeworld.name << " (" << empire_data.homeworld << "), type " << homeworld.subtype << '\n';
}
