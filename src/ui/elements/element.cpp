#include <ui/elements/element.hpp>

std::function<void(Element*)> Element::setActive;
std::function<void(Element*)> Element::unsetActive;

std::function<void(Element*)> Element::setSelected;
std::function<void(Element*)> Element::unsetSelected;

void Element::setPosition(const sf::Vector2f& position)
{
    frame.setPosition(position);
}

const sf::RectangleShape& Element::getFrame() const
{
    return frame;
}

void Element::setState(State state)
{
    this->state = state;
}

void Element::activate()
{
    setActive(this);
}

void Element::deactivate()
{
    unsetActive(this);
    setToBase();
}

void Element::select()
{
    setSelected(this);
}

void Element::deselect()
{
    unsetSelected(this);
}

bool Element::available() const
{
    return (state != UNAVAILABLE);
}

bool Element::highlighted() const
{
    return (state == HIGHLIGHTED);
}

bool Element::active() const
{
    return (state == ACTIVE);
}

bool Element::selected() const
{
    return (state == SELECTED);
}

void Element::setToBase()
{
    setState(base_state);
}

bool Element::clickLeft()
{
    return false;
}
bool Element::releaseLeft()
{
    return false;
}

bool Element::textEntered(const sf::Event&) { return false; }
bool Element::keyPressed(sf::Keyboard::Key) { return false; }
bool Element::clickRight() { return false; }
bool Element::releaseRight() { return false; }
void Element::scroll(float) { }

sf::Vector2f Element::getPosition()
{
    return frame.getPosition();
}

sf::Vector2f Element::getSize()
{
    return frame.getSize();
}

