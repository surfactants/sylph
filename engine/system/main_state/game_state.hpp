#pragma once

#include <game/game.hpp>

#include <menu/state/menu.hpp>

#include "main_state.hpp"

class Game_State : public Main_State {
public:
    Game_State();

    virtual void update(float delta_time) override;
    virtual void handleInput(const sf::Event& event) override;

    std::function<void()> openPauseMenu;

    void setGameState(Game::State new_game);

private:
    Game* game;

    std::map<Game::State, std::unique_ptr<Game>> states;
};
