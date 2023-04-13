#pragma once

#include <SFML/Graphics.hpp>

#include <tuple>
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

    virtual void scroll(float delta) override;

    std::vector<Command> getCommands();

private:
    Key_String key_string;

    std::vector<Command> commands;

    std::vector<std::tuple<sf::Text, Button, Command*>> rows;

    Button* highlighted_button { nullptr };
    Command* highlighted_command { nullptr };
    Button* active_button { nullptr };
    Command* active_command { nullptr };

    constexpr static unsigned int csize { 44 };
    constexpr static unsigned int text_size { 42 };

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
