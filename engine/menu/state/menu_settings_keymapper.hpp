#pragma once

#include <system/input/command.hpp>

#include <menu/elements/keymapper.hpp>

#include "menu.hpp"

class Menu_Settings_Keymapper : public Menu {
public:
    Menu_Settings_Keymapper(std::function<std::vector<Command>()>     loadCommands
                          , std::function<void(std::vector<Command>)> saveCommands);

    virtual void enterState() override;
    virtual void exitState() override;

    virtual void update(const sf::Vector2i& mpos) override;

    std::function<std::vector<Command>()> loadCommands;
    std::function<void(std::vector<Command>)> saveCommands;

private:
    Keymapper keymapper;

    void save();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
