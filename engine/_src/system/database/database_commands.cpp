#include <system/database/database_commands.hpp>

std::vector<Command> Database_Commands::read()
{
    std::vector<Command> pkg;

    selectTable("COMMANDS");

    while (step()) {
        int col = 0;
        Command c;
        std::string key = toString(col++);
        c.key = key_string.toKey(key);
        c.key = sf::Keyboard::A;
        c.press = toString(col++);
        c.release = toString(col++);

        pkg.push_back(c);
    }

    finalize();

    return pkg;
}

void Database_Commands::write(std::vector<Command> pkg)
{
    //selectTable("COMMANDS");

    deleteMissingKeys(pkg);

    for (const auto& c : pkg) {
        std::string key = key_string.toString(c.key);

        std::string update_query = "UPDATE COMMANDS SET PRESS='"
            + c.press + "', RELEASE='"
            + c.release + "'"
            + "WHERE KEY ='" + key +"';";

        execute(update_query);

        std::string insert_query = "INSERT INTO COMMANDS (KEY, PRESS, RELEASE) SELECT '"
            + key + "', '"
            + c.press + "', '"
            + c.release + "'"
            + "WHERE (Select Changes() = 0);";

        execute(insert_query);
    }
}

void Database_Commands::deleteMissingKeys(const std::vector<Command>& pkg)
{
    std::string delete_query = "DELETE FROM COMMANDS WHERE KEY NOT IN (";
    size_t n = pkg.size();
    for (size_t i = 0; i < n; i++) {
        delete_query += "'" + key_string.toString(pkg[i].key) + "'";
        if (i < n - 1) { [[likely]]
            delete_query += ",";
        }
    }
    delete_query += ")";
    execute(delete_query);
}
