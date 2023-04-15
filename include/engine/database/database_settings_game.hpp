#pragma once

#include <vector>

#include <game/data/game_settings.hpp>

#include "database.hpp"

class Database_Settings_Game : protected Database {
public:
    Database_Settings_Game();

    Game_Settings read();
    Game_Settings readDefaults();

    void write(Game_Settings settings);
};
