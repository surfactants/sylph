#include <engine/database/database_settings_game.hpp>

Database_Settings_Game::Database_Settings_Game()
{
    pkey = "ID";
}

Game_Settings Database_Settings_Game::read()
{
    Game_Settings settings;

    selectByKey("GAME_SETTINGS", "ACTIVE");
    step();
    int col = 1;
    settings.difficulty = sqlite3_column_int(statement, col++);
    settings.speed = sqlite3_column_int(statement, col++);
    finalize();
    return settings;
}

Game_Settings Database_Settings_Game::readDefaults()
{
    Game_Settings settings;

    selectByKey("GAME_SETTINGS", "DEFAULT");
    step();
    int col = 1;
    settings.difficulty = sqlite3_column_int(statement, col++);
    settings.speed = sqlite3_column_int(statement, col++);
    finalize();

    return settings;
}

void Database_Settings_Game::write(Game_Settings s)
{
    selectByKey("GAME_SETTINGS", "ACTIVE");

    std::string update_query = "UPDATE GAME_SETTINGS SET DIFFICULTY=" + std::to_string(s.difficulty)
        + ", SPEED=" + std::to_string(s.speed)
        + " WHERE ID='ACTIVE';";

        execute(update_query);
}
