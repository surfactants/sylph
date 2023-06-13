#pragma once

#include <engine/audio/audio.hpp>
#include <engine/system/game_state.hpp>

#include <ui/menu/menu.hpp>

#include "main_state.hpp"

class Menu_State : public Main_State {
public:
    Menu_State(Audio& audio, Game_State* game);

    virtual void update(float delta_time) override;
    virtual void handleInput(const sf::Event& event) override;

    virtual void windowResize(const sf::Vector2u& w_size) override;

    void setState(UI::State new_menu);

    std::map<UI::State, std::unique_ptr<Menu>> menus;

    struct State_Record {
        UI::State state;
        Menu* ptr;
    };

    State_Record current;
    State_Record last;
};
