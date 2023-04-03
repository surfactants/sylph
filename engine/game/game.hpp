#pragma once

class Game {
public:
    Game();

    enum State {
        PLAY
    };

    virtual void update(float delta_time) = 0;
};
