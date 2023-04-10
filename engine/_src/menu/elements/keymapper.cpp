#include <menu/elements/keymapper.hpp>

#include <util/text.hpp>

Keymapper::Keymapper()
{
    setState(READY);
}

void Keymapper::load(std::vector<Command> new_commands, sf::Font& font)
{
    commands = new_commands;
    rows.clear();

    float button_offset = 32.f;

    sf::Vector2f pos(button_offset * 1.5f, button_offset * 1.5f);

    for (const auto& c : commands) {
        std::string key = key_string.toString(c.key);

        sf::Vector2f button_pos(pos);
        sf::Vector2f button_size = sf::Vector2f(96.f, 96.f);

        Button button(key, font, csize, Button::READY);
        button.setSize(button_size);
        button.setPosition(button_pos);

        sf::Text text;
        text.setFont(font);
        text.setString(c.press);
        text.setCharacterSize(csize);
        centerText(text);

        sf::Vector2f text_pos(button_pos);
        text_pos.x += button_size.x + button_offset;
        text_pos.x += (text.getGlobalBounds().left + text.getGlobalBounds().width) / 2.f;
        text.setPosition(text_pos);

        rows.push_back(std::make_pair(text, std::move(button)));

        pos.y += button_size.y + button_offset;
    }

    setScrollable(pos.y);
}

bool Keymapper::update(const sf::Vector2i& mpos)
{
    bool cnt = Scrollable::contains(mpos);
    switch (state) {
        default:
            // this should never happen, log this
            setState(READY);
            [[fallthrough]]; // just in case, process as normal
        case READY:
            if (cnt) {
                setState(HIGHLIGHTED);
            }
            else {
                break;
            }
            [[fallthrough]]; // allow same-frame update when the mouse enters the frame
        case HIGHLIGHTED:
            if (cnt) {
                sf::Vector2i pos(translateGlobalPos(mpos));
                int n = rows.size();
                for (int i = 0; i < n; i++) {
                    if (active_index != i) {
                        rows[i].second.update(pos);
                    }
                }
            }
            else {
                setState(READY);
            }
            break;
    }
    return cnt;
}

void Keymapper::clickLeft()
{
    active_index = -1;
    if (active_index >= 0) {
        rows[active_index].second.setState(READY);
    }
    int n = rows.size();
    for (int i = 0; i < n; i++) {
        if (rows[i].second.highlighted()) {
            active_index = i;
            rows[i].second.clickLeft();
            activate();
            return;
        }
    }
}

void Keymapper::activate()
{
    Menu_Element::activate();
    setState(ACTIVE);
}

void Keymapper::deactivate()
{
    if (active_index >= 0) {
        rows[active_index].second.setState(READY);
        active_index = -1;
    }
    Menu_Element::deactivate();
    setState(READY);
}

void Keymapper::releaseLeft()
{}

void Keymapper::clickRight()
{
    if (active_index >= 0) {
        deactivate();
    }
}

void Keymapper::keyPressed(sf::Keyboard::Key k)
{
    if (k == sf::Keyboard::Escape) {
        deactivate();
        return;
    }
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
        rows[active_index].second.setState(READY);
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
