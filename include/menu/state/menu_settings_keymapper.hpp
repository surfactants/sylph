#pragma once

#include <engine/input/command.hpp>

#include <menu/elements/keymapper.hpp>

#include "menu.hpp"

class Menu_Settings_Keymapper : public Menu {
public:
    Menu_Settings_Keymapper(std::function<void(std::vector<Command>)> saveCommands);

    virtual void enterState() override;
    virtual void exitState() override;

    std::function<void(std::vector<Command>)> saveCommands;

private:
    Keymapper keymapper;

    void load();
    void loadDefaults();
    void save();
};
