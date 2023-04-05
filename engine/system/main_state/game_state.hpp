#pragma once

#include <game/game.hpp>

#include <menu/state/menu.hpp>

#include <system/input/input_package.hpp>

#include "main_state.hpp"

class Game_State : public Main_State {
public:
    Game_State(std::function<void()> open_pause);

    virtual void update(float delta_time) override;
    virtual void handleInput(const sf::Event& event) override;

    void setGameState(Game::State new_game);

    void loadInput(Input_Package input);

private:
    Game* game;

    Game::State game_state { Game::PLAY };

    std::map<Game::State, std::unique_ptr<Game>> states;

    Input_Package* input;

    std::unordered_map<Game::State, Input_Package> input_map;
};
