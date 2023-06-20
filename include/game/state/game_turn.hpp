#pragma once

#include "game.hpp"

class Game_Turn : public Game {
public:
    Game_Turn() = default;

    virtual void update(const float delta_time) override;
};
