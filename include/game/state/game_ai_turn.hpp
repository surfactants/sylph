#pragma once

#include "game.hpp"

class Game_AI_Turn : public Game {
public:
    Game_AI_Turn() = default;

    virtual void update(const float delta_time) override;
};
