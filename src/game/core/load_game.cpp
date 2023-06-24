#include <game/core/load_game.hpp>

Load_Game::Load_Game(ECS_Core* core, std::filesystem::path file)
    : Database(file.string())
    , core { core }
{
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
    bodyInfo();
    civData();
    collisionRect();
    entityData();
    hierarchy();
    polygonTile();
    resource();
    tile();
    transform();

    passCivs();
    passTiles();
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
        sf::Vector2f min;
        min.x = toFloat(col++);
        min.y = toFloat(col++);
        sf::Vector2f size;
        size.x = toFloat(col++);
        size.y = toFloat(col++);
        rect.setPosition(min);
        rect.setSize(size);

        core->components.addComponent(e, rect);
    }
}

void Load_Game::date()
{
    selectTable(serializer.to_string[Component::DATE]);

    while (step()) {
        int col { 0 };
        Entity e = toInt(col++);

        Date date;
        date.year = toInt(col++);
        date.month = toInt(col++);

        core->components.addComponent(e, date);
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
    selectTable(serializer.to_string[Component::RESOURCE]);

    while (step()) {
        int col { 0 };
        Entity e = toInt(col++);

        Resource resource;
        const std::string r_string = toString(col++);

        std::istringstream rstream { r_string };

        std::string r;

        while (std::getline(rstream, r, ';')) {
            auto it = r.find(',');
            std::string type_string = r.substr(0, it);
            Resource::Type type = Resource::fromString(type_string);
            float val = std::stof(r.substr(it + 1));
            resource.values[type] = val;
        }

        core->components.addComponent(e, resource);
    }
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
