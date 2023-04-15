#pragma once

#include <engine/audio/audio.hpp>
#include <engine/system/game_state.hpp>

#include <menu/state/menu.hpp>

#include "main_state.hpp"

class Menu_State : public Main_State {
public:
    Menu_State(Audio& audio, Game_State* game);

    virtual void update(float delta_time) override;
    virtual void handleInput(const sf::Event& event) override;

    void setMenuState(Menu::State new_menu);

    Menu* menu;

    std::map<Menu::State, std::unique_ptr<Menu>> menus;

    Menu::State current_menu { Menu::MAIN };
    Menu::State last_menu { Menu::MAIN };
};
