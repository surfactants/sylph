#pragma once

#include "menu.hpp"

class Menu_Settings_Game : public Menu {
public:
    Menu_Settings_Game();

    void load();
    void loadDefaults();
    virtual void save() override;

    virtual void enterState() override;

private:
    Dropdown<int> dropdown_difficulty;
    Dropdown<int> dropdown_speed;
};

