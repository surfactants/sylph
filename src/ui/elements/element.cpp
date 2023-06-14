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

void Element::textEntered(const sf::Event& event) { }
void Element::keyPressed(sf::Keyboard::Key key) { }
void Element::clickRight() { }
void Element::releaseRight() { }
void Element::scroll(float delta) { }

