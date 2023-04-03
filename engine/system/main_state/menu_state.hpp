#pragma once

#include "main_state.hpp"

#include <audio/audio.hpp>

#include <menu/state/menu.hpp>

class Menu_State : public Main_State {
public:
    Menu_State(Audio& audio);

    virtual void update(float delta_time) override;
    virtual void handleInput(const sf::Event& event) override;

    void setMenuState(Menu::State new_menu);

    Menu* menu;

    std::map<Menu::State, std::unique_ptr<Menu>> menus;

    Menu::State current_menu { Menu::MAIN };
    Menu::State last_menu { Menu::MAIN };
};
