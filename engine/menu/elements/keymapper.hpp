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
    virtual void clickLeft() override;
    virtual void releaseLeft() override;
    virtual void keyPressed(sf::Keyboard::Key) override;
    virtual void clickRight() override;

    virtual void activate() override;
    virtual void deactivate() override;

    std::vector<Command> getCommands();

    sf::RectangleShape test_rect;

private:
    Key_String key_string;

    std::vector<Command> commands;

    std::vector<std::pair<sf::Text, Button>> rows;

    int active_index = -1;

    constexpr static unsigned int csize { 48 };
    constexpr static unsigned int text_size { 42 };

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
