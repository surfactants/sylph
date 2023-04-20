#pragma once

#include <engine/input/input_package.hpp>

#include <game/data/new_game_data.hpp>
#include <game/state/game.hpp>

#include <menu/state/menu.hpp>

#include "main_state.hpp"

class Game_State : public Main_State {
public:
    Game_State(std::function<void()> open_pause);

    virtual void update(float delta_time) override;
    virtual void handleInput(const sf::Event& event) override;

    void setGameState(Game::State state);

    void loadInput(Input_Package input);

    void loadCommands(std::vector<Command> new_commands);
    void loadSettings(Game_Settings settings);

    void newGame(New_Game_Data data);
    void loadGame();
    void newToPlay();

    void clear();

private:
    std::unique_ptr<Game> game { nullptr };

    Game::State game_state;

    std::map<Game::State, std::unique_ptr<Game>> states;

    std::vector<Command> commands {};

    std::function<void()> stringToFunction(std::string str);

    Input_Package* input;

    std::unordered_map<Game::State, Input_Package> input_map;

    Game_Settings settings;

    New_Game_Data data;
};
