#pragma once

#include <functional>
#include <memory>

#include <game/data/game_settings.hpp>

#include <game/system/accelerator.hpp>
#include <game/system/component_manager.hpp>
#include <game/system/entity_manager.hpp>
#include <game/system/renderer.hpp>

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

    virtual void clickLeft() = 0;
    virtual void releaseLeft() = 0;

    virtual void clickRight() = 0;
    virtual void releaseRight() = 0;

    static std::function<void(Game::State)> setGameState;

    const Entity_Manager& getEntities() const;

    void reset();

    static Renderer* getRenderer();

protected:
    static Game_Settings settings;

    Entity_Manager entities;

    static Component_Manager components;

    static Renderer renderer;

    Accelerator accelerator;

    void addEntity(Entity e, std::vector<Component*> c);
};
