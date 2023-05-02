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
    void loadNums();
    void loadSettings(Game_Settings settings);

    void newGame(New_Game_Data data);
    void loadGame();
    void newToPlay();

    void clear();

    void numPress(unsigned int i);

private:
    std::unique_ptr<Game> game { nullptr };

    Game::State game_state;

    std::vector<Command> commands {};

    std::function<void()> stringToFunction(std::string str);

    Input_Package* input;

    std::unordered_map<Game::State, Input_Package> input_map;

    Game_Settings settings;

    New_Game_Data data;

    sf::FloatRect window_frame;

    sf::Vector2f translateGlobalPos(const sf::Vector2i& v);
    void moveFrame(sf::Vector2f velocity);

    float zoom { 1.f };
    float max_zoom { 4.f };
    float min_zoom { 0.5f };
    float zoom_step { 0.1f };
    constexpr static float zoom_speed_factor { 3.f };

    void scroll(float delta);

    void clickLeft();
    void clickRight();
};
