#include <game/core/save_game.hpp>

#include <game/core/component_serializer.hpp>

Save_Game::Save_Game(ECS_Core* core, std::filesystem::path file)
    : core { core }
{
    if (std::filesystem::exists(file)) {
        std::filesystem::remove(file);
    }

    rc = sqlite3_open(file.string().c_str(), &db);

    createTables();
    writeInfo();
    writeEntities();
    writeSystems();
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
      , MINUTES_PLAYED INT NOT NULL\
      );";
      // todo blob for preview image

    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);

    for (const auto& system : core->systems.map) {
        sql = "CREATE TABLE " + system.first + "(ENTITY INT PRIMARY KEY NOT NULL);";
        rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    }
}

void Save_Game::writeInfo()
{
}

void Save_Game::writeEntities()
{
    Component_Serializer serialize_component;

    unsigned int size = toInt(Component::SIZE);

    std::map<unsigned int, std::string> insert_component;


    for (unsigned int i = 0; i < size; i++) {
        Component c = toComponent(i);
        std::string cname = serialize_component.to_string[c];

        std::string itype = serialize_component.types(c, false);
        insert_component[i] = "INSERT INTO ["
                            + cname
                           + "]"
                            + itype
                            + " VALUES";

        // typeid.name(T) produces a numeric identifier prepending the string
        // sqlite does not allow table names to start with numbers
        // wrapping table name with brackets supercedes this

        std::string ctype = serialize_component.types(c, true);
        ctype.pop_back();
        ctype += ")";
        std::string create = "CREATE TABLE ["
                           + cname
                           + "]"
                            + ctype
                           + ";";

        rc = sqlite3_exec(db, create.c_str(), nullptr, nullptr, nullptr);

    }

    std::string sql = "INSERT INTO ENTITIES(UID, SIGNATURE) VALUES";
    for (Entity e = 0; e < MAX_ENTITIES; e++) {
        Signature s = core->entities.signature(e);
        if (s.none()) {
            continue;
        }
        sql += "("
            + std::to_string(e)
            + ", "
            + s.to_string()
            + "),";

        unsigned int size = toInt(Component::SIZE);

        for (unsigned int i = 0; i < size; i++) {
            if (s.test(i)) {
                insert_component[i] += serialize_component.values(toComponent(i), e) + ",";
            }
        }
    }
    sql.pop_back();
    sql += ";";
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);

    for (unsigned int i = 0; i < size; i++) {
        insert_component[i].pop_back();
        insert_component[i] += ";";
        rc = sqlite3_exec(db, insert_component[i].c_str(), nullptr, nullptr, nullptr);
    }
}

void Save_Game::writeSystems()
{
    for (const auto& system : core->systems.map) {
        std::string sql = "INSERT INTO " + system.first + "(ENTITY) VALUES";
        for (const auto& entity : system.second->entities) {
        sql += "("
            + std::to_string(entity)
            + "),";
        }
        sql.pop_back();
        sql += ";";
        rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    }
}
