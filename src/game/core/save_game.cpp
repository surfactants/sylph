#include <game/core/save_game.hpp>

#include <iostream>

Save_Game::Save_Game(Component_Manager& components
        , Entity_Manager& entities
        , std::filesystem::path file)
    : components { components }
    , entities { entities }
    , file { file }
{
    std::cout << "\n\nSAVING GAME AT " << file.string();
    bool file_exists { false };
    if (std::filesystem::exists(file)) {
        std::filesystem::remove(file);
    }

    rc = sqlite3_open(file.string().c_str(), &db);

    createTables();
    writeInfo();
    writeEntities();
    writeComponents();
}

void Save_Game::createTables()
{
    std::string sql = "CREATE TABLE ENTITIES(\
        UID INT PRIMARY KEY NOT NULL\
      , SIGNATURE TEXT NOT NULL\
      );";

    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);

    sql = "CREATE TABLE INFO(\
        PLAYER_UID INT PRIMARY KEY NOT NULL\
      , PLAYER_NAME INT NOT NULL\
      , YEAR INT NOT NULL\
      );";

    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
}

void Save_Game::writeInfo()
{
}

void Save_Game::writeEntities()
{
    std::string sql = "INSERT INTO ENTITIES(UID, SIGNATURE) VALUES";
    for (Entity e = 0; e < MAX_ENTITIES; e++) {
        Signature s = entities.signature(e);
        if (s.none()) {
            continue;
        }
        sql += "("
            + std::to_string(e)
            + ", "
            + s.to_string()
            + "),";
    }
    sql.pop_back();
    sql += ";";
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
}

void Save_Game::writeComponents()
{
}
