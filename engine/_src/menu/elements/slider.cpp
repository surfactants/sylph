#include <menu/elements/slider.hpp>

#include <system/event/event_bus.hpp>

//////////////////////////////////////////////////////////////

const sf::Vector2f Slider::container_size = sf::Vector2f(384.f, 48.f);

const float Slider::offset = 3.f;

const float Slider::scroll_factor = 5.f;

Slider::Slider(std::string ntitle)
{
    fillChangeCallback = [](float){};

    container.setSize(container_size);
    container.setFillColor(sf::Color::Transparent);
    container.setOutlineThickness(1);

    fill.setSize(sf::Vector2f(0.f, container.getSize().y - (offset * 2.f)));
    fill.setFillColor(Palette::blue);

    title.setString(ntitle);
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(title, states);
    target.draw(container, states);
    target.draw(fill, states);
    target.draw(label, states);
}

void Slider::set(sf::Vector2f pos, sf::Font& font)
{
    title.setFont(font);

    label.setFont(font);

    title.setPosition(pos);

    pos.y += title.getLocalBounds().height + title.getLocalBounds().top + (offset * 2.f);

    container.setPosition(pos);
    fill.setPosition(pos + sf::Vector2f(offset, offset));

    pos.x += container.getSize().x - (label.getLocalBounds().width + label.getLocalBounds().left) - (offset * 4.f);
    pos.y += (fill.getSize().y - (label.getLocalBounds().height + label.getLocalBounds().top)) / 2.f - offset;
    label.setPosition(pos);

    title.setFillColor(Palette::white);
    label.setFillColor(Palette::white);

    container.setOutlineColor(Palette::white);
}

void Slider::setFill(float f)
{
    int last_fill = static_cast<int>(getFill());
    if (f < 0.f) {
        f = 0.f;
    }
    else if (f > 100.f) {
        f = 100.f;
    }
    int new_fill = static_cast<int>(f);

    if (new_fill != last_fill) {
        Event_Bus::publish(Event(Event::SOUND, Event::Tag::SLIDER_MOVED));
        fill.setSize(sf::Vector2f((f / 100.f) * (container.getSize().x - (offset * 2.f)), fill.getSize().y));
        label.setString(std::to_string(new_fill));
        fill_factor = 100.f * (fill.getSize().x / (container.getSize().x - (offset * 2.f)));
        fillChangeCallback(fill_factor);
    }
}

void Slider::findFill(int mX)
{
    static float f;
    if (mX <= container.getPosition().x + offset) {
        f = 0.f;
    }
    else if (mX >= container.getPosition().x + container.getSize().x - offset) {
        f = 1.f;
    }
    else {
        f = (mX - container.getPosition().x) / container.getSize().x;
    }

    f *= 100.f;

    setFill(f);
}

float Slider::getFill() const
{
    return fill_factor;
}

void Slider::scroll(float delta)
{
    if (delta < 0) {
        setFill(getFill() - scroll_factor);
    }
    else if (delta > 0) {
        setFill(getFill() + scroll_factor);
    }
}

bool Slider::checkMouse(const sf::Vector2i& mpos)
{
    return container.getGlobalBounds().contains(mpos.x, mpos.y);
}

void Slider::update(const sf::Vector2i& mpos)
{
    if (changing) {
        findFill(mpos.x);
    }
    else {
        moused = checkMouse(mpos);
    }
}

bool Slider::unclick()
{
    changing = false;
    return changing;
}

bool Slider::click()
{
    if (moused) {
        changing = true;
    }
    return changing;
}

float Slider::revert()
{
    setFill(start_fill);
    return fill_factor;
}

void Slider::finalize()
{
    start_fill = getFill();
}
