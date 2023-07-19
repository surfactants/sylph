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
        core->info.minutes_played = toInt(col++);
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
    collisionRect();
    entityData();
    hierarchy();
    transform();
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
        vectorize(h.children, toString(col++));
        vectorize(h.parents, toString(col++));
        vectorize(h.neighbors, toString(col++));

        core->components.addComponent(e, h);
    }
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
