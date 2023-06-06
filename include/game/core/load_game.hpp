#pragma once

#include <sqlite3.h>

#include <filesystem>

#include <engine/database/database.hpp>

#include <game/core/component_serializer.hpp>
#include <game/core/ecs_core.hpp>

class Load_Game : public Database{
public:
    Load_Game(ECS_Core* core, std::filesystem::path file);

private:
    ECS_Core* core;

    Component_Serializer serializer;

    void readInfo();
    void readEntities();
    void readComponents();
};
