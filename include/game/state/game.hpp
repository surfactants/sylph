#pragma once

#include <functional>
#include <memory>

#include <game/core/ecs_core.hpp>
#include <game/core/game_info.hpp>

#include <game/data/game_settings.hpp>

#include <game/core/component_manager.hpp>
#include <game/core/entity_manager.hpp>
#include <game/core/system_manager.hpp>

class Game {
public:
    Game() = default;

    enum State {
        NEW,
        PLAY,
        UI
    };

    virtual void update(const float delta_time) = 0;

    virtual void loadSettings(Game_Settings settings);

    virtual void clickLeft() = 0;
    virtual void releaseLeft() = 0;

    virtual void clickRight() = 0;
    virtual void releaseRight() = 0;

    virtual void clickMiddle() = 0;
    virtual void releaseMiddle() = 0;

    static std::function<void(Game::State)> setGameState;

    void reset();

    static std::unique_ptr<ECS_Core> core;
    static Game_Settings settings;

    //static Entity_Manager entities;
    //static Component_Manager components;
    //static System_Manager systems;
    //static Game_Info info;
};
