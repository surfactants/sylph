#include <menu/elements/button.hpp>

#include <resources/palette.hpp>

#include <system/event/event_bus.hpp>

#include <util/text.hpp>

//////////////////////////////////////////////////////////////

const float Button::padding = 8;

Button::Button(std::string nlabel, sf::Font& font, unsigned int csize, State base)
{
    base_state = base;

    label.setFont(font);
    label.setString(nlabel);
    label.setCharacterSize(csize);
    centerText(label);

    frame.setSize(sf::Vector2f(label.getLocalBounds().left + label.getLocalBounds().width + (padding * 2.f),
        label.getLocalBounds().top + label.getLocalBounds().height + (padding * 2.f)));
    frame.setOrigin(frame.getSize() / 2.f);

    setState(base);

    target = [](){};
}

Button::Button(std::string nlabel, sf::Font& font, std::function<void()> target, unsigned int csize, State base)
    : target{ target }
{
    base_state = base;
    label.setFont(font);
    label.setString(nlabel);
    label.setCharacterSize(csize);
    centerText(label);

    frame.setSize(sf::Vector2f(label.getLocalBounds().left + label.getLocalBounds().width + (padding * 2.f),
        label.getLocalBounds().top + label.getLocalBounds().height + (padding * 2.f)));
    frame.setOrigin(frame.getSize() / 2.f);

    setState(base);
}

bool Button::update(const sf::Vector2i& mpos)
{
    switch (state) {
        case READY:
            if (contains(mpos)) {
                setState(HIGHLIGHTED);
                return true;
            }
            return false;
        case HIGHLIGHTED:
            if (!contains(mpos)) {
                setState(READY);
                return false;
            }
            return true;
        case ACTIVE:
            if (!contains(mpos)) {
                setState(READY);
                return false;
            }
            return true;
        default:
            return false;
    }
}

void Button::setPosition(sf::Vector2f pos)
{
    label.setPosition(pos);
    frame.setPosition(pos);
}

sf::Vector2f Button::getPosition()
{
    return label.getPosition();
}

void Button::setSize(sf::Vector2f size)
{
    frame.setSize(size);
    frame.setOrigin(size / 2.f);
}

sf::Vector2f Button::getSize()
{
    return frame.getSize();
}

void Button::click()
{
    setState(ACTIVE);
    Event_Bus::publish(Event(Event::SOUND, Event::Tag::BUTTON_PRESSED));
}

void Button::endClick()
{
    if (active()) {
        setState(base_state);
        Event_Bus::publish(Event(Event::SOUND, Event::Tag::BUTTON_TRIGGERED));
        target();
    }
}

void Button::setState(Button::State state)
{
    this->state = state;
    switch (state) {
        case UNAVAILABLE:
            frame.setFillColor(Palette::gray_dark);
            label.setFillColor(Palette::black);
            break;
        case READY:
            label.setFillColor(Palette::white);
            frame.setFillColor(Palette::gray);
            break;
        case HIGHLIGHTED:
            frame.setFillColor(Palette::blue);
            label.setFillColor(Palette::white);
            break;
        case ACTIVE:
            frame.setFillColor(Palette::green);
            label.setFillColor(Palette::white);
            break;
    }
}

void Button::setLabel(std::string text)
{
    label.setString(text);
    centerText(label);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(frame, states);
    target.draw(label, states);
}
