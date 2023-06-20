#pragma once

#include "game.hpp"

class Game_Simulate : public Game {
public:
    Game_Simulate() = default;

    virtual void update(const float delta_time) override;
};
