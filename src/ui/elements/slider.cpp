#include <ui/elements/slider.hpp>

#include <engine/event/event_bus.hpp>

//////////////////////////////////////////////////////////////

const sf::Vector2f Slider::frame_size = sf::Vector2f(384.f, 48.f);

const float Slider::offset = 3.f;

const float Slider::scroll_factor = 5.f;

Slider::Slider(std::string ntitle, unsigned int title_size)
{
    fillChangeCallback = [](float) {};

    frame.setSize(frame_size);
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineThickness(1);

    fill.setSize(sf::Vector2f(0.f, frame.getSize().y - (offset * 2.f)));
    fill.setFillColor(Palette::blue);

    setFill(100.f);

    title.setString(ntitle);
    title.setCharacterSize(title_size);
}

void Slider::set(sf::Vector2f pos, const sf::Font& font)
{
    title.setFont(font);
    label.setFont(font);

    title.setFillColor(Palette::white);
    label.setFillColor(Palette::white);
    frame.setOutlineColor(Palette::white);

    setPosition(pos);
}

void Slider::setPosition(const sf::Vector2f& pos)
{
    title.setPosition(pos);
    sf::Vector2f sub_pos { pos };
    sub_pos.y += title.getLocalBounds().top + title.getLocalBounds().height + (padding * 2.f);
    frame.setPosition(sub_pos);
    fill.setPosition(sub_pos + sf::Vector2f(offset, offset));

    sub_pos.x += frame.getSize().x - (label.getLocalBounds().width + label.getLocalBounds().left) - (offset * 4.f);
    sub_pos.y += (fill.getSize().y - (label.getLocalBounds().height + label.getLocalBounds().top)) / 2.f - offset;
    label.setPosition(sub_pos);
}

void Slider::deactivate()
{
    changing = false;
    moused = false;
    Element::deactivate();
}

sf::Vector2f Slider::getSize()
{
    sf::Vector2f size;
    const sf::FloatRect title_bounds = title.getLocalBounds();
    const sf::Vector2f text_size(title_bounds.left + title_bounds.width, title_bounds.top + title_bounds.height);
    const sf::Vector2f frame_size = frame.getSize();

    if (text_size.x > frame_size.x) {
        size.x = text_size.x;
    }
    else {
        size.x = frame_size.x;
    }

    size.y = frame_size.y + (frame.getPosition().y - title.getPosition().y);

    return size;
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

bool Slider::update(const sf::Vector2i& mpos)
{
    if (changing) {
        findFill(mpos.x);
        return true;
    }
    else {
        moused = contains(mpos);
        return moused;
    }
}

bool Slider::releaseLeft()
{
    changing = false;
    return (moused);
}

bool Slider::clickLeft()
{
    if (moused) {
        changing = true;
        return true;
    }
    return false;
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

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(title, states);
    target.draw(frame, states);
    target.draw(fill, states);
    target.draw(label, states);
}
