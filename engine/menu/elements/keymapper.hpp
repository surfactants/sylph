#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include <menu/elements/button.hpp>
#include <menu/elements/scrollable.hpp>

#include <system/input/command.hpp>
#include <system/input/key_string.hpp>

class Keymapper : public Scrollable, public sf::Drawable {
public:
    Keymapper();

    void load(std::vector<Command> commands, sf::Font& font, const unsigned int csize);

    void update(const sf::Vector2i& mpos);

    std::vector<Command> getCommands();

private:
    Key_String key_string;

    std::vector<Command> commands;

    std::vector<std::pair<sf::Text, Button>> rows;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
