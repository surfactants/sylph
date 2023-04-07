#include <menu/elements/keymapper.hpp>

#include <util/text.hpp>

Keymapper::Keymapper()
{
    sf::Vector2f s(9999.f, 9999.f);
    test_rect.setSize(s);
    test_rect.setOrigin(s / 2.f);
    test_rect.setFillColor(sf::Color::Black);
}

void Keymapper::load(std::vector<Command> new_commands, sf::Font& font)
{
    commands = new_commands;
    rows.clear();

    float button_offset = 32.f;

    sf::Vector2f pos(button_offset * 3.f, button_offset);

    for (const auto& c : commands) {
        std::string key = key_string.toString(c.key);

        sf::Text text;
        text.setFont(font);
        text.setString(c.press);
        centerText(text);
        text.setPosition(pos);

        sf::Vector2f button_pos(pos);
        sf::Vector2f button_size = sf::Vector2f(96.f, 96.f);

        Button button(key, font, csize, Button::READY);
        button.setSize(button_size);

        button_pos.x = Scrollable::frame.width - button_offset - (button_size.x / 2.f);
        button.setPosition(button_pos);
        pos.y += button_size.y + button_offset;

        rows.push_back(std::make_pair(text, std::move(button)));
    }

    setScrollable(pos.y);
}

bool Keymapper::update(const sf::Vector2i& mpos)
{
    bool cnt = Scrollable::contains(mpos);
    if (cnt) {
        sf::Vector2i pos(translateGlobalPos(mpos));
        int n = rows.size();
        for (int i = 0; i < n; i++) {
            if (active_index != i) {
                rows[i].second.update(pos);
            }
        }
    }
    return cnt;
}

void Keymapper::click()
{
    int n = rows.size();
    for (int i = 0; i < n; i++) {
        if (rows[i].second.highlighted()) {
            if (active_index >= 0) {
                rows[active_index].second.setState(READY);
            }
            active_index = i;
            rows[i].second.click();
            setState(ACTIVE);
            break;
        }
    }
}

void Keymapper::endClick()
{}

void Keymapper::rightClick()
{
    if (active_index >= 0) {
        rows[active_index].second.setState(READY);
        active_index = -1;
    }
}

void Keymapper::keyPressed(sf::Keyboard::Key k)
{
    if (active_index >= 0 && k != sf::Keyboard::Unknown) {
        // attempt swap
        int n = rows.size();
        for (int i = 0; i < n; i++) {
            if (i != active_index && commands[i].key == k) {
                commands[i].key = commands[active_index].key;
                std::string swap = key_string.toString(commands[active_index].key);
                rows[i].second.setLabel(swap);
            }
        }

        // set
        commands[active_index].key = k;
        std::string key = key_string.toString(k);
        rows[active_index].second.setLabel(key);
        rows[active_index].second.setState(Menu_Element::READY);
        setState(READY);
        active_index = -1;
    }
}

std::vector<Command> Keymapper::getCommands()
{
    return commands;
}

void Keymapper::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.setView(view);
    target.draw(test_rect, states);
    for (const auto& row : rows) {
        target.draw(row.first, states);
        target.draw(row.second, states);
    }
    target.draw(scrollbar, states);
}
