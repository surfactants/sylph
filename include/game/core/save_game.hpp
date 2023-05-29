#pragma once

#include <sqlite3.h>

#include <filesystem>

#include <game/system/component_manager.hpp>
#include <game/system/entity_manager.hpp>
#include <game/system/system_manager.hpp>

class Save_Game {
public:
    Save_Game(Component_Manager& components
            , Entity_Manager& entities
            , std::filesystem::path file);

private:
    Component_Manager& components;
    Entity_Manager& entities;

    std::filesystem::path file;

    void createTables();
    void writeInfo();
    void writeEntities();
    void writeComponents();

    sqlite3* db { nullptr };

    int rc;
};
