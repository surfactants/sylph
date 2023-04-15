#pragma once

#include <game/data/new_game_data.hpp>

#include "game.hpp"

class New_Game : public Game {
public:
    New_Game(New_Game_Data data);

    virtual void update(float delta_time) override;

    virtual void loadSettings(Game_Settings settings) override;
};
