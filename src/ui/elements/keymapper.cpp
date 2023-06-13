#include <ui/elements/keymapper.hpp>

#include <engine/resources/palette.hpp>
#include <engine/util/text.hpp>

Keymapper::Keymapper(const sf::Font& font)
    : Toggle_Scroller(font)
{}

void Keymapper::load(std::vector<Command> commands)
{
    reset();
    rows.clear();

    //float button_offset = 32.f;

    button_pos = sf::Vector2f(button_offset, button_offset);
    button_size = sf::Vector2f(192.f, 128.f);

    for (auto& c : commands) {
        std::string key = key_string.toString(c.key);

        Row r;

        // button
        r.button = Button(key, font, csize, Button::READY);
        r.button.setSize(button_size);
        r.button.setPosition(button_pos);

        // text
        r.text.setFont(font);
        r.text.setString(c.press);
        r.text.setCharacterSize(csize);
        centerText(r.text);

        sf::Vector2f text_pos(button_pos + (button_size / 2.f));
        text_pos.x += button_size.x + button_offset;
        text_pos.x += (r.text.getGlobalBounds().left + r.text.getGlobalBounds().width) / 2.f;
        r.text.setPosition(text_pos);

        // data
        r.data = c;

        rows.push_back(std::move(r));

        button_pos.y += button_size.y + button_offset;
    }

    setScrollable(button_pos.y);
}

void Keymapper::keyPressed(sf::Keyboard::Key k)
{
    if (k == sf::Keyboard::Escape) {
        deactivate();
    }
    else if (active_row && k != sf::Keyboard::Unknown) {
        // attempt swap
        for (auto& row : rows) {
            if (row.data.key == k) {
                row.data.key = active_row->data.key;
                row.button.setLabel(active_row->button.getLabel());
                break;
            }
        }
        std::string key = key_string.toString(k);
        active_row->data.key = k;
        active_row->button.setLabel(key);
        active_row->button.setState(READY);
        active_row = nullptr;
        setState(READY);
    }
}
