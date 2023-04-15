#pragma once

#include <game/state/game.hpp>

class Game {
public:
    Game();

    enum State {
        PLAY,
        UI
    };

    virtual void update(float delta_time) = 0;
};
