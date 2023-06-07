#include <game/core/load_game.hpp>

#include <engine/util/sfml_stream.hpp>

Load_Game::Load_Game(ECS_Core* core, std::filesystem::path file)
    : Database(file.string())
    , core { core }
{
    std::cout << "loading\n";
    readInfo();
    readEntities();
    readComponents();
}

void Load_Game::readInfo()
{
    selectTable("INFO");
    while (step()) {
        int col = 0;

        core->info.player = toInt(col++);
        core->info.player_name = toString(col++);
        core->info.year = toInt(col++);
        core->info.minutes_played = toInt(col++);
        core->info.world_bounds.left = toFloat(col++);
        core->info.world_bounds.top = toFloat(col++);
        core->info.world_bounds.width = toFloat(col++);
        core->info.world_bounds.height = toFloat(col++);
    }
}

void Load_Game::readEntities()
{
    selectTable("ENTITIES");
    while (step()) {
        int col = 0;

        Entity e = toInt(col++);
        Signature s(toString(col++));

        core->entities.define(e, s);
    }

    core->entities.readAvailable();
}

void Load_Game::readComponents()
{
    std::cout << "\n\nREADING COMPONENTS...\n";
    bodyInfo();
    std::cout << "\tbody info read\n";
    civData();
    std::cout << "\tciv data read\n";
    collisionRect();
    std::cout << "\tcollision rect read\n";
    entityData();
    std::cout << "\tentity data read\n";
    hierarchy();
    std::cout << "\thierarchy read\n";
    polygonTile();
    std::cout << "\tpolygon tile read\n";
    resource();
    std::cout << "\tresource read\n";
    tile();
    std::cout << "\ttile read\n";
    transform();
    std::cout << "\ttransform read\n";

    passCivs();
    passTiles();

    std::cout << "READING COMPLETE!\n";
}

void Load_Game::bodyInfo()
{
    selectTable(serializer.to_string[Component::BODY_INFO]);

    while (step()) {
        int col { 0 };
        Entity e = toInt(col++);

        Body_Info info;
        info.type = toString(col++);
        info.subtype = toString(col++);
        info.radius = toFloat(col++);
        info.orbit = toFloat(col++);
        info.temperature = toFloat(col++);
        info.light = toFloat(col++);
        readColor(col, info.color);
        info.owned = toInt(col++);
        info.owner = toInt(col++);

        core->components.addComponent(e, info);
    }
}

void Load_Game::civData()
{
    selectTable(serializer.to_string[Component::CIVILIZATION_DATA]);

    while (step()) {
        int col { 0 };
        Entity e = toInt(col++);

        Civilization_Data data;
        data.capital_system = toInt(col++);
        data.homeworld = toInt(col++);
        vectorize(data.systems, toString(col++));
        data.population = toFloat(col++);
        readColor(col, data.color);

        core->components.addComponent(e, data);
    }
}

void Load_Game::collisionRect()
{
    selectTable(serializer.to_string[Component::COLLISION_RECT]);

    while (step()) {
        int col { 0 };
        Entity e = toInt(col++);

        Collision_Rect rect;
        sf::Vector2f min(toFloat(col++), toFloat(col++));
        //sf::Vector2f max(toFloat(col++), toFloat(col++)); // debug, TODO erase this after confirmation of load functioning when new saves can be generated
        sf::Vector2f size(toFloat(col++), toFloat(col++));
        rect.setPosition(min);
        rect.setSize(size);

        core->components.addComponent(e, rect);
    }
}

void Load_Game::entityData()
{
    selectTable(serializer.to_string[Component::ENTITY_DATA]);

    while (step()) {
        int col { 0 };
        Entity e = toInt(col++);

        Entity_Data data;
        data.name = toString(col++);
        data.description = toString(col++);

        core->components.addComponent(e, data);
    }
}

void Load_Game::hierarchy()
{
    selectTable(serializer.to_string[Component::HIERARCHY]);

    while (step()) {
        int col { 0 };
        Entity e = toInt(col++);

        Hierarchy h;
        vectorize(h.child, toString(col++));
        vectorize(h.parent, toString(col++));

        core->components.addComponent(e, h);
    }
}

void Load_Game::polygonTile()
{
    selectTable(serializer.to_string[Component::POLYGON_TILE]);

    while (step()) {
        int col { 0 };
        Entity e = toInt(col++);

        Polygon_Tile tile;
        vectorize(tile.vertices, toString(col++));
        readColor(col, tile.color, true);

        core->components.addComponent(e, tile);
    }
}

void Load_Game::resource()
{
    // todo
}

void Load_Game::tile()
{
    // todo
}

void Load_Game::transform()
{
    selectTable(serializer.to_string[Component::TRANSFORM]);

    while (step()) {
        int col { 0 };
        Entity e = toInt(col++);

        Transform trans;
        trans.position.x = toFloat(col++);
        trans.position.y = toFloat(col++);
        trans.rotation = toFloat(col++);
        trans.scale = toFloat(col++);

        core->components.addComponent(e, trans);
    }
}

void Load_Game::passCivs()
{
    selectTable("CIVILIZATIONS");
    while (step()) {
        core->systems.civilizations.add(toInt(0));
    }
}

void Load_Game::passTiles()
{
    selectTable("TILE_SYSTEM");
    while (step()) {
        core->systems.tile_system.addTile(toInt(0));
    }
}
