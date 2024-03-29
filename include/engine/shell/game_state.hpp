#pragma once

#include <filesystem>

#include <engine/input/input_package.hpp>

#include <game/core/component_serializer.hpp>

#include <game/data/new_game_data.hpp>

#include <game/state/game.hpp>

#include <ui/hud/hud.hpp>

#include "main_state.hpp"

class Game_State : public Main_State {
public:
    //Game_State() = default;
    Game_State(std::function<void()> open_pause);

    virtual void update(const float delta_time) override;
    virtual void handleInput(const sf::Event& event) override;

    virtual void windowResize(const sf::Vector2u& w_size) override;

    void setGameState(Game::State state);
    void setHUDState(UI::State state);

    void loadCommands(std::vector<Command> new_commands);
    void loadSettings(Game_Settings settings);

    void newGame(New_Game_Data data);
    void loadGame(std::filesystem::path load_path);
    void newToPlay();

    void clear();

    void registration();

    template <typename T>
    void registerComponent(Component c)
    {
        std::string t(typeid(T).name());

        auto get = Game::core->components.registerComponent<T>();
        System::getComponent<T> = get;
        UI::getComponent<T> = get;
        Game::core->systems.getComponent<T> = get;

        Component_Serializer::to_component[t] = c;
        Component_Serializer::to_string[c] = t;
        Component_Serializer::getComponent<T> = get;

        HUD::getComponent<T> = get;
    }

private:
    std::unique_ptr<Game> game { nullptr };

    Game::State game_state;

    std::vector<Command> commands {};

    HUD* hud { nullptr };
    std::map<UI::State, std::unique_ptr<HUD>> hud_states;

    std::function<void()> stringToFunction(std::string str);

    Input_Package input;

    Game_Settings settings;

    New_Game_Data data;

    sf::Vector2u w_size;

    std::map<std::string, std::function<void()>> string_to_function;
    void loadFunctions();

    sf::Vector2f translateGlobalPos(const sf::Vector2i& v);

    void clickLeft();
    void releaseLeft();
    void clickRight();
    void releaseRight();
    void clickMiddle();
    void releaseMiddle();
    void scroll(const float delta);

    void windowResize();
};
