#pragma once

#include <functional>
#include <memory>

#include <game/data/game_settings.hpp>

#include <game/system/accelerator.hpp>
#include <game/system/component_manager.hpp>
#include <game/system/entity_manager.hpp>
#include <game/system/renderer.hpp>

#include <game/world/world.hpp>

class Game {
public:
    Game();
    Game(const Game& g);

    ~Game();

    enum State {
        NEW,
        PLAY,
        UI
    };

    virtual void update(float delta_time, const sf::Vector2f& mpos) = 0;

    virtual void loadSettings(Game_Settings settings);

    virtual void clickLeft() // = 0;
    {
        world->activateCell();
    }

    virtual void clickRight() // = 0;
    {
        world->deactivateCell();
    }

    static std::function<void(Game::State)> setGameState;

    World* getWorld();
    const Entity_Manager& getEntities() const;

    void deleteWorld();

    static Renderer* getRenderer();

protected:
    static Game_Settings settings;

    Entity_Manager entities;

    static std::unique_ptr<World> world;

    static Component_Manager components;

    static Renderer renderer;

    Accelerator accelerator;
};
