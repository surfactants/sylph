#include <ui/elements/element.hpp>

std::function<void(Element*)> Element::setActive;
std::function<void(Element*)> Element::setInactive;

void Element::setPosition(const sf::Vector2f& position)
{
    frame.setPosition(position);
}

const sf::RectangleShape& Element::getFrame()
{
    return frame;
}

void Element::setState(State state)
{
    this->state = state;
}

void Element::deactivate()
{
    setInactive(this);
    setToBase();
}

void Element::activate()
{
    setActive(this);
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

void Element::setToBase()
{
    setState(base_state);
}

void Element::textEntered(const sf::Event& event) { }
void Element::keyPressed(sf::Keyboard::Key) { }
void Element::clickRight() { }
void Element::releaseRight() { }
void Element::scroll(float delta) { }

