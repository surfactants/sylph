#pragma once

#include "game.hpp"

class New_Game : public Game {
public:
    New_Game();

    virtual void update(float delta_time) override;

    virtual void loadSettings(Game_Settings settings) override;
};
