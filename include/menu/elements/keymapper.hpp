#pragma once

#include <SFML/Graphics.hpp>

#include <tuple>
#include <vector>

#include <engine/input/command.hpp>
#include <engine/input/key_string.hpp>

#include <menu/elements/button.hpp>
#include <menu/elements/scrollable.hpp>

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

    typedef std::tuple<sf::Text, std::unique_ptr<Button>, Command*> Key_Row;

    std::vector<Key_Row> rows;

    Key_Row* highlighted_row { nullptr };
    Key_Row* active_row { nullptr };

    Button* activeButton();
    Button* highlightedButton();

    constexpr static unsigned int csize { 44 };
    constexpr static unsigned int text_size { 42 };

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
