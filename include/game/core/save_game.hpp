#pragma once

#include <sqlite3.h>

#include <filesystem>

#include <game/core/ecs_core.hpp>

class Save_Game {
public:
    Save_Game(ECS_Core* core, std::filesystem::path file);

private:
    ECS_Core* core;

    void createTables();
    void writeInfo();
    void writeEntities();
    void writeSystems();
    void writeComponents();

    sqlite3* db { nullptr };

    int rc;
};
