#pragma once

#include <functional>

#include <game/data/game_settings.hpp>
#include <game/system/entity_manager.hpp>
#include <game/world/world.hpp>

class Game {
public:
    Game();

    enum State {
        NEW,
        PLAY,
        UI
    };

    virtual void update(float delta_time) = 0;

    virtual void loadSettings(Game_Settings settings);

    static std::function<void(Game::State)> setGameState;

    const World& getWorld() const;
    const Entity_Manager& getEntities() const;

protected:
    static Game_Settings settings;

    Entity_Manager entities;

    World world;
};
