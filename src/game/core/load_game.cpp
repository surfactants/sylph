#include <game/core/load_game.hpp>

#include <engine/util/sfml_stream.hpp>

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
    }
}

void Load_Game::readEntities()
{
    selectTable("ENTITIES");
    while (step()) {
        int col = 0;

        Entity e = toInt(col++);
        Signature s(toString(col++));
    }
}

void Load_Game::readComponents()
{
}
