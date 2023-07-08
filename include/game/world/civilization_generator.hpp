#pragma once

#include <game/core/ecs_core.hpp>

#include <game/data/new_game_data.hpp>

class Civilization_Generator {
public:
    Civilization_Generator(New_Game_Data data, ECS_Core* core);

private:
    New_Game_Data data;

    ECS_Core* core;

    void generatePlayer();
    void generateAI();

    void print(Entity civilization);
};
