#pragma once

#include "game.hpp"

class Game_Player_Turn : public Game {
public:
    Game_Player_Turn() = default;

    virtual void update(const float delta_time) override;
};
