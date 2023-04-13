#include <menu/elements/keymapper.hpp>

#include <resources/palette.hpp>

#include <util/text.hpp>

Keymapper::Keymapper()
{
    setState(READY);
    scrollbar.setSize(sf::Vector2f(12.f, 12.f));
    setBackground(Palette::gray_dark);
}

void Keymapper::load(std::vector<Command> new_commands, sf::Font& font)
{
    commands = new_commands;
    rows.clear();

    float button_offset = 32.f;

    sf::Vector2f pos(button_offset, button_offset);

    for (auto& c : commands) {
        std::string key = key_string.toString(c.key);

        sf::Vector2f button_pos(pos);
        sf::Vector2f button_size = sf::Vector2f(192.f, 128.f);

        Button button(key, font, csize, Button::READY);
        button.setSize(button_size);
        button.setPosition(button_pos);

        sf::Text text;
        text.setFont(font);
        text.setString(c.press);
        text.setCharacterSize(csize);
        centerText(text);

        sf::Vector2f text_pos(button_pos + (button_size / 2.f));
        text_pos.x += button_size.x + button_offset;
        text_pos.x += (text.getGlobalBounds().left + text.getGlobalBounds().width) / 2.f;
        text.setPosition(text_pos);

        rows.push_back(std::make_tuple(text, button, &c));

        pos.y += button_size.y + button_offset;
    }

    setScrollable(pos.y);
}

void Keymapper::scroll(float delta)
{
    Scrollable::scroll(delta, sf::Vector2f(sf::Mouse::getPosition()));
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
                sf::Vector2i trans_pos(translateGlobalPos(mpos));
                if (highlighted_row && std::get<Button>(*highlighted_row).update(trans_pos)) {
                    break;
                }
                else {
                    highlighted_row = nullptr;
                    for (auto& row : rows) {
                        if (&row != active_row && std::get<Button>(row).update(trans_pos)) {
                            highlighted_row = &row;
                        }
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
    if (highlighted_row) {
        active_row = highlighted_row;
        std::get<Button>(*active_row).setState(ACTIVE);
        highlighted_row = nullptr;
        activate();
    }
    else if (state == READY) {
        if (active_row) {
            std::get<Button>(*active_row).setState(READY);
            deactivate();
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
    if (active_row) {
        std::get<Button>(*active_row).setState(READY);
        active_row = nullptr;
    }
    Menu_Element::deactivate();
    setState(READY);
}

void Keymapper::releaseLeft()
{}

void Keymapper::clickRight()
{
    deactivate();
}

void Keymapper::keyPressed(sf::Keyboard::Key k)
{
    if (k == sf::Keyboard::Escape) {
        deactivate();
    }
    else if (active_row && k != sf::Keyboard::Unknown) {
        // attempt swap
        for (auto& [t, b, c] : rows) {
            if (c->key == k) {
                c->key = std::get<Command*>(*active_row)->key;
                b.setLabel(std::get<Button>(*active_row).getLabel());
                break;
            }
        }

        std::string key = key_string.toString(k);
        auto& [t, b, c] = *active_row;
        c->key = k;
        b.setLabel(key);
        b.setState(READY);
        active_row = nullptr;
        setState(READY);
    }
}

std::vector<Command> Keymapper::getCommands()
{
    return commands;
}

void Keymapper::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.setView(view);
    target.draw(background, states);
    for (const auto& [t, b, c] : rows) {
        target.draw(t, states);
        target.draw(b, states);
    }
    target.draw(scrollbar, states);
}
