#pragma once

#include <game/state/game.hpp>

#include <menu/state/menu.hpp>

#include <engine/input/input_package.hpp>

#include "main_state.hpp"

class Game_State : public Main_State {
public:
    Game_State(std::function<void()> open_pause);

    virtual void update(float delta_time) override;
    virtual void handleInput(const sf::Event& event) override;

    void setGameState(Game::State new_game);

    void loadInput(Input_Package input);

    void loadCommands(std::vector<Command> new_commands);

private:
    Game* game;

    Game::State game_state { Game::PLAY };

    std::map<Game::State, std::unique_ptr<Game>> states;

    std::vector<Command> commands {};

    std::function<void()> stringToFunction(std::string str);

    Input_Package* input;

    std::unordered_map<Game::State, Input_Package> input_map;
};