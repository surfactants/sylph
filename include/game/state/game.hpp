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
        TURN,
        SIMULATE
    };

    void initializeCore();

    virtual void update(const float delta_time) = 0;

    virtual void loadSettings(Game_Settings settings);

    virtual void clickLeft();
    virtual void releaseLeft();

    virtual void clickRight();
    virtual void releaseRight();

    virtual void clickMiddle();
    virtual void releaseMiddle();

    static std::function<void(Game::State)> setGameState;

    static std::function<sf::Vector2f(sf::View)> relativeMousePos;

    void reset();

    static std::unique_ptr<ECS_Core> core;
    static Game_Settings settings;
    static System_Manager* systems;

protected:
    void controlCamera(const sf::Vector2f& mpos, const float delta_time);
    void contextUpdate(const sf::Vector2f& mpos);
};
