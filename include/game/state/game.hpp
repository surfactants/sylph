#pragma once

#include <functional>
#include <memory>

#include <game/data/game_settings.hpp>

#include <game/system/component_manager.hpp>
#include <game/system/entity_manager.hpp>
#include <game/system/renderer.hpp>
#include <game/system/system_manager.hpp>

class Game {
public:
    Game() = default;

    enum State {
        NEW,
        PLAY,
        UI
    };

    virtual void update(float delta_time, const sf::Vector2f& mpos) = 0;

    virtual void loadSettings(Game_Settings settings);

    virtual void clickLeft() = 0;
    virtual void releaseLeft() = 0;

    virtual void clickRight() = 0;
    virtual void releaseRight() = 0;

    static std::function<void(Game::State)> setGameState;

    void reset();

    sf::View base_view;

    sf::View* current_view { &base_view };

    static Game_Settings settings;
    static Entity_Manager entities;
    static Component_Manager components;
    static System_Manager systems;
    static Renderer renderer;
};
