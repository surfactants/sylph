#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include <menu/elements/button.hpp>
#include <menu/elements/scrollable.hpp>

#include <system/input/command.hpp>
#include <system/input/key_string.hpp>

#include "menu_element.hpp"

class Keymapper : public Scrollable, public Menu_Element {
public:
    Keymapper();

    void load(std::vector<Command> new_commands, sf::Font& font);

    virtual bool update(const sf::Vector2i& mpos) override;
    virtual void click() override;
    virtual void endClick() override;
    virtual void keyPressed(sf::Keyboard::Key) override;
    virtual void rightClick() override;

    std::vector<Command> getCommands();

    sf::RectangleShape test_rect;

private:
    Key_String key_string;

    std::vector<Command> commands;

    std::vector<std::pair<sf::Text, Button>> rows;

    int active_index = -1;

    constexpr static unsigned int csize { 48 };

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
