#pragma once

#include <game/data/game_settings.hpp>

class Game {
public:
    Game();

    enum State {
        PLAY,
        UI
    };

    virtual void update(float delta_time) = 0;

    virtual void loadSettings(Game_Settings settings);

protected:
    static Game_Settings settings;
};
