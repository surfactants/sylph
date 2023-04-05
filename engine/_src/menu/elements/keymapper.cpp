#include <menu/elements/keymapper.hpp>

Keymapper::Keymapper()
{}

void Keymapper::load(std::vector<Command> commands, sf::Font& font, const unsigned int csize)
{
    this->commands = commands;
    rows.clear();

    float button_offset = 32.f;

    sf::Vector2f pos(button_offset, button_offset);

    for (const auto& c : commands) {
        std::string key = key_string.toString(c.key);

        sf::Text text;
        text.setFont(font);
        text.setPosition(pos);
        text.setString(key);

        Button button(c.press, font, csize);
        sf::Vector2f size = button.getSize();
        pos += (size / 2.f);
        button.setPosition(pos);
        pos -= (size / 2.f);
        pos.y += button_offset;

        rows.push_back(std::make_pair(text, std::move(button)));
    }

    setScrollable(pos.y);
}

void Keymapper::update(const sf::Vector2i& mpos)
{
    for (auto& row : rows) {
        row.second.update(mpos);
    }
}

std::vector<Command> Keymapper::getCommands()
{
    return commands;
}

void Keymapper::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.setView(view);
    for (const auto& row : rows) {
        target.draw(row.first, states);
        target.draw(row.second, states);
    }
    target.draw(scrollbar, states);
}
