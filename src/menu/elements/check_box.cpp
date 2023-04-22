#include <menu/elements/check_box.hpp>

#include <engine/event/event_bus.hpp>
#include <engine/resources/palette.hpp>

Check_Box::Check_Box(sf::Font& font, std::string ls, unsigned int csize)
{
    label.setFont(font);
    label.setCharacterSize(csize);
    label.setFillColor(Palette::white);
    label.setString(ls);

    frame.setSize(sf::Vector2f(48, 48));
    frame.setOutlineThickness(stroke_default);

    setState(READY);
    setChecked(false);
}

bool Check_Box::update(const sf::Vector2i& mpos)
{
    bool has_mouse = contains(mpos);
    switch (state) {
        case READY:
            if (has_mouse) {
                setState(HIGHLIGHTED);
            }
            break;
        case HIGHLIGHTED:
            if (!has_mouse) {
                setState(READY);
            }
            break;
        default:
            break;
    }

    return has_mouse;
}

void Check_Box::setState(State state)
{
    this->state = state;
    switch (state) {
        case HIGHLIGHTED:
            frame.setOutlineThickness(stroke_highlight);
            break;
        default:
            frame.setOutlineThickness(stroke_default);
    }
}

void Check_Box::clickLeft()
{
    if (highlighted()) {
        setChecked(!checked);
    }
}

void Check_Box::releaseLeft()
{
}

void Check_Box::setChecked(bool state)
{
    checked = state;
    if (checked) {
        frame.setFillColor(Palette::green);
        Event_Bus::publish(Event(Event::SOUND, Event::Tag::CHECK_BOX_YES));
    }
    else {
        frame.setFillColor(sf::Color::Transparent);
        Event_Bus::publish(Event(Event::SOUND, Event::Tag::CHECK_BOX_NO));
    }
}

void Check_Box::setPosition(sf::Vector2f pos)
{
    frame.setPosition(pos);
    pos.x += frame.getSize().x + 8;
    pos.y -= 8;
    label.setPosition(pos);
}

void Check_Box::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(frame, states);
    target.draw(label, states);
}
