#pragma once

#include <game/data/game_settings.hpp>

#include "menu.hpp"

class Menu_Settings_Game : public Menu {
public:
    Menu_Settings_Game(std::function<void(Game_Settings)> save_settings);

    void load();
    void loadDefaults();
    virtual void save() override;

    virtual void enterState() override;

    std::function<void(Game_Settings)> save_to_game;

private:
    Dropdown<int> dropdown_difficulty;
    Dropdown<int> dropdown_speed;
};

