#include <game/world/civilization_generator.hpp>

#include <engine/util/prng.hpp>

#include <iostream>

Civilization_Generator::Civilization_Generator(New_Game_Data data
    , Component_Manager& components
    , Entity_Manager& entities
    , System_Manager& systems)
    : data { data }
    , components { components }
    , entities { entities }
    , systems { systems }
{
    generatePlayer();
    for (size_t i = 0; i < 9; i++) {
        generateAI();
    }
}

void Civilization_Generator::generatePlayer()
{
    Entity civilization = entities.create();
    Signature sig;
    sig.flip(toInt(Component::ENTITY_DATA));
    sig.flip(toInt(Component::EMPIRE_DATA));
    entities.define(civilization, sig);

    Entity_Data entity_data;
    entity_data.name = data.player_name;
    entity_data.description = "player_civilization_desc";

    Entity capital_system = systems.tile_system.random();
    auto children = components.getComponent<Hierarchy>(capital_system).child;
    size_t body_index;
    do {
        body_index = prng::number(children.size());
    } while (body_index == 0 && children.size() != 0);
    Entity homeworld = children[body_index];

    Civilization_Data civilization_data;
    civilization_data.capital_system = capital_system;
    civilization_data.homeworld = homeworld;
    civilization_data.systems.push_back(capital_system);
    civilization_data.color = data.player_color;

    components.addComponent(civilization, entity_data);
    components.addComponent(civilization, civilization_data);

    components.getComponent<Polygon_Tile>(capital_system).color = data.player_color;
    auto& system_info = components.getComponent<Body_Info>(capital_system);
    system_info.owned = true;
    system_info.owner = civilization;

    auto& system_data = components.getComponent<Entity_Data>(capital_system);
    system_data.name = data.home_system;

    auto& star_info = components.getComponent<Entity_Data>(children.front());
    star_info.name = data.home_system;

    auto& home_info = components.getComponent<Body_Info>(homeworld);
    home_info.owned = true;
    home_info.owner = civilization;

    auto& home_data = components.getComponent<Entity_Data>(homeworld);
    home_data.name = data.homeworld;

    systems.tile_system.repaintTile(capital_system);

    print(civilization);
}

void Civilization_Generator::generateAI()
{
    Entity civilization = entities.create();
    Signature sig;
    sig.flip(toInt(Component::ENTITY_DATA));
    sig.flip(toInt(Component::EMPIRE_DATA));
    entities.define(civilization, sig);

    Entity_Data entity_data;
    entity_data.name = "ai civilization " + std::to_string(civilization);
    entity_data.description = "ai_civilization_desc";

    Entity capital_system;
    do {
        capital_system = systems.tile_system.random();
    } while (components.getComponent<Body_Info>(capital_system).owned);
    auto children = components.getComponent<Hierarchy>(capital_system).child;
    size_t body_index;
    do {
        body_index = prng::number(children.size());
    } while (body_index == 0 && children.size() != 0);
    Entity homeworld = children[body_index];

    Civilization_Data civilization_data;
    civilization_data.capital_system = capital_system;
    civilization_data.homeworld = homeworld;
    civilization_data.systems.push_back(capital_system);

    int r = prng::number(0, 255);
    int g = prng::number(0, 255);
    int b = prng::number(0, 255);

    sf::Color color(r, g, b);

    civilization_data.color = color;

    components.addComponent(civilization, entity_data);
    components.addComponent(civilization, civilization_data);

    components.getComponent<Polygon_Tile>(capital_system).color = color;
    auto& system_info = components.getComponent<Body_Info>(capital_system);
    system_info.owned = true;
    system_info.owner = civilization;

    auto& home_info = components.getComponent<Body_Info>(homeworld);
    home_info.owned = true;
    home_info.owner = civilization;

    systems.tile_system.repaintTile(capital_system);

    print(civilization);
}

void Civilization_Generator::print(Entity civilization)
{
    auto entity_data = components.getComponent<Entity_Data>(civilization);
    auto civilization_data = components.getComponent<Civilization_Data>(civilization);
    auto capital_info = components.getComponent<Entity_Data>(civilization_data.capital_system);
    auto homeworld_info = components.getComponent<Body_Info>(civilization_data.homeworld);
    auto homeworld_data = components.getComponent<Entity_Data>(civilization_data.homeworld);

    std::cout << "generated civilization '" << entity_data.name << "' (" << civilization << ")\n";
    std::cout << "\tlocated in the " << capital_info.name << " system (" << civilization_data.capital_system << ")\n";
    std::cout << "\thomeworld is " << homeworld_data.name << " (" << civilization_data.homeworld << "), type " << homeworld_info.subtype << '\n';
}
