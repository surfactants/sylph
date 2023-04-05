#pragma once

#include <game/game.hpp>

class Game {
public:
    Game();

    enum State {
        PLAY,
        UI
    };

    virtual void update(float delta_time) = 0;
};
