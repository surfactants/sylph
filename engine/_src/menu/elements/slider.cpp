#include <menu/elements/slider.hpp>

#include <system/event/event_bus.hpp>

//////////////////////////////////////////////////////////////

const sf::Vector2f Slider::frame_size = sf::Vector2f(384.f, 48.f);

const float Slider::offset = 3.f;

const float Slider::scroll_factor = 5.f;

Slider::Slider(std::string ntitle)
{
    fillChangeCallback = [](float){};

    frame.setSize(frame_size);
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineThickness(1);

    fill.setSize(sf::Vector2f(0.f, frame.getSize().y - (offset * 2.f)));
    fill.setFillColor(Palette::blue);

    setFill(100.f);

    title.setString(ntitle);
    title.setCharacterSize(48);
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(title, states);
    target.draw(frame, states);
    target.draw(fill, states);
    target.draw(label, states);
}

void Slider::set(sf::Vector2f pos, sf::Font& font)
{
    title.setFont(font);

    label.setFont(font);

    title.setPosition(pos);

    pos.y += title.getLocalBounds().height + title.getLocalBounds().top + (offset * 2.f);

    frame.setPosition(pos);
    fill.setPosition(pos + sf::Vector2f(offset, offset));

    pos.x += frame.getSize().x - (label.getLocalBounds().width + label.getLocalBounds().left) - (offset * 4.f);
    pos.y += (fill.getSize().y - (label.getLocalBounds().height + label.getLocalBounds().top)) / 2.f - offset;
    label.setPosition(pos);

    title.setFillColor(Palette::white);
    label.setFillColor(Palette::white);

    frame.setOutlineColor(Palette::white);
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
        fill.setSize(sf::Vector2f((f / 100.f) * (frame.getSize().x - (offset * 2.f)), fill.getSize().y));
        label.setString(std::to_string(new_fill));
        fill_factor = 100.f * (fill.getSize().x / (frame.getSize().x - (offset * 2.f)));
        fillChangeCallback(fill_factor);
    }
}

void Slider::findFill(int mX)
{
    static float f;
    if (mX <= frame.getPosition().x + offset) {
        f = 0.f;
    }
    else if (mX >= frame.getPosition().x + frame.getSize().x - offset) {
        f = 1.f;
    }
    else {
        f = (mX - frame.getPosition().x) / frame.getSize().x;
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
    return frame.getGlobalBounds().contains(mpos.x, mpos.y);
}

bool Slider::update(const sf::Vector2i& mpos)
{
    if (changing) {
        findFill(mpos.x);
        return true;
    }
    else {
        moused = checkMouse(mpos);
        return moused;
    }
}

void Slider::endClick()
{
    changing = false;
}

void Slider::click()
{
    if (moused) {
        changing = true;
    }
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
