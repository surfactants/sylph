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
                if (highlighted_button && highlighted_button->update(trans_pos)) {
                    break;
                }
                else {
                    highlighted_button = nullptr;
                    highlighted_command = nullptr;
                    for (auto& [t, b, c] : rows) {
                        if (&b != active_button && b.update(trans_pos)) {
                            highlighted_button = &b;
                            highlighted_command = c;
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
    if (highlighted_button) {
        active_button = highlighted_button;
        active_command = highlighted_command;
        active_button->setState(ACTIVE);
        highlighted_button = nullptr;
        highlighted_command = nullptr;
        activate();
    }
    else if (state == READY) {
        if (active_button) {
            active_button->setState(READY);
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
    if (active_button) {
        active_button->setState(READY);
        active_button = nullptr;
        active_command = nullptr;
    }
    Menu_Element::deactivate();
    setState(READY);
}

void Keymapper::releaseLeft()
{}

void Keymapper::clickRight()
{
    if (active_button) {
        deactivate();
    }
}

void Keymapper::keyPressed(sf::Keyboard::Key k)
{
    if (k == sf::Keyboard::Escape) {
        deactivate();
    }
    else if (active_button && k != sf::Keyboard::Unknown) {
        // attempt swap
        for (auto& [t, b, c] : rows) {
            if (c->key == k) {
                c->key = active_command->key;
                b.setLabel(active_button->getLabel());
                break;
            }
        }

        active_command->key = k;
        std::string key = key_string.toString(k);
        active_button->setLabel(key);
        active_button->setState(READY);
        active_button = nullptr;
        active_command = nullptr;
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
