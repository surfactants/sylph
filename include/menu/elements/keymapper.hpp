#pragma once

#include <SFML/Graphics.hpp>

#include <tuple>
#include <vector>

#include <engine/input/command.hpp>
#include <engine/input/key_string.hpp>

#include "toggle_scroller.hpp"

class Keymapper : public Toggle_Scroller<Command> {
public:
    Keymapper(const sf::Font& font);

    virtual void keyPressed(sf::Keyboard::Key k) override;

    void load(std::vector<Command> commands);

private:
    Key_String key_string;
};
