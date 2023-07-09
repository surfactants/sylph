#include <ui/elements/panel.hpp>

#include <engine/util/text.hpp>

Panel::Panel()
{
    frame.setFillColor(Palette::gray_dark);
    frame.setOutlineColor(Palette::white);
    frame.setOutlineThickness(outline);
}

Panel::Panel(const sf::Vector2f pos, const sf::Vector2f size)
{
    setPosition(pos);
    setSize(size);

    frame.setFillColor(Palette::gray_dark);
    frame.setOutlineColor(Palette::white);
    frame.setOutlineThickness(outline);
}

bool Panel::update(const sf::Vector2i& mpos)
{
    bool cnt = frame.getGlobalBounds().contains(mpos.x, mpos.y);
    if (active) {
        if (active->update(mpos)) {
            moused = active;
            return cnt;
        }
    }

    if (moused) {
        if (!moused->update(mpos)) {
            moused = nullptr;
        }
        else {
            return cnt;
        }
    }

    for (auto& element : elements) {
        if (element->update(mpos)) {
            moused = element;
            break;
        }
    }
    return cnt;
}

void Panel::setPosition(const sf::Vector2f& pos)
{
    frame.setPosition(pos);

    const sf::Vector2f size = frame.getSize();

    left_pos = pos + sf::Vector2f(panel_padding, panel_padding);
    center_pos = pos + sf::Vector2f((size.x / 2.f), panel_padding);
    right_pos = pos + sf::Vector2f(size.x - panel_padding, panel_padding);
}

void Panel::setSize(const sf::Vector2f& size)
{
    frame.setSize(size);

    const sf::Vector2f pos = frame.getPosition();

    left_pos = pos + sf::Vector2f(panel_padding, panel_padding);
    center_pos = pos + sf::Vector2f((size.x / 2.f), panel_padding);
    right_pos = pos + sf::Vector2f(size.x - panel_padding, panel_padding);
}

void Panel::addElement(Element* element, Place place)
{
    sf::Vector2f pos;
    const sf::Vector2f size = element->getSize();

    switch (place) {
        case LEFT:
            pos = left_pos;
            left_pos.y += size.y + padding;
            break;
        case CENTER:
            pos = center_pos;
            pos.x -= (size.x / 2.f);
            center_pos.y += size.y + padding;
            break;
        case RIGHT:
            pos = right_pos;
            pos.x -= size.x;
            right_pos.y += size.y + padding;
            break;
    }
    element->setPosition(pos);
    elements.push_back(element);

    renderer.push_front(element);
}

void Panel::addText(sf::Text* t, const Place place, const float wrap_width)
{
    sf::Vector2f pos;
    wrapText(*t, wrap_width);
    const sf::FloatRect bounds = t->getLocalBounds();
    const sf::Vector2f size(bounds.left + bounds.width, bounds.top + bounds.height);

    switch (place) {
        case LEFT:
            pos = left_pos;
            left_pos.y += size.y + padding * 2.f;
            break;
        case CENTER:
            pos = center_pos;
            pos.x -= (size.x / 2.f);
            center_pos.y += size.y + padding * 2.f;
            break;
        case RIGHT:
            pos = right_pos;
            pos.x -= size.x;
            right_pos.y += size.y + padding * 2.f;
            break;
    }
    t->setPosition(pos);
    text.push_back(t);

    renderer.push_front(t);
}

void Panel::clear()
{
    elements.clear();
    text.clear();

    const sf::Vector2f size = frame.getSize();
    const sf::Vector2f pos = frame.getPosition();

    left_pos = pos + sf::Vector2f(panel_padding, panel_padding);
    center_pos = pos + sf::Vector2f((size.x / 2.f), panel_padding);
    right_pos = pos + sf::Vector2f(size.x - panel_padding, size.y + panel_padding);
}

bool Panel::clickLeft()
{
    if (moused) {
        active = moused;
        return moused->clickLeft();
    }
    return false;
}

bool Panel::releaseLeft()
{
    if (moused) {
        return moused->releaseLeft();
    }
    return false;
}

bool Panel::clickRight()
{
    if (active) {
        active->setToBase();
        active = nullptr;
        return true;
    }
    return false;
}

bool Panel::releaseRight()
{
    if (active) {
        active->setToBase();
        active = nullptr;
        return true;
    }
    return false;
}

bool Panel::textEntered(const sf::Event& event)
{
    if (active) {
        return active->textEntered(event);
    }
    return false;
}

bool Panel::keyPressed(sf::Keyboard::Key key)
{
    if (active) {
        return active->keyPressed(key);
    }
    return false;
}

void Panel::deactivate()
{
    if (active) {
        active->deactivate();
    }
    active = nullptr;
    moused = nullptr;
}

void Panel::reset()
{
}

void Panel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(frame, states);
    for (const auto& element : renderer) {
        target.draw(*element, states);
        target.setView(*view);
    }
}
