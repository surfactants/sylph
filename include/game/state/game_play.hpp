#pragma once

#include "game.hpp"

class Game_Play : public Game {
public:
    Game_Play();

    explicit Game_Play(const Game& g);

    virtual void update(float delta_time) override;
};
