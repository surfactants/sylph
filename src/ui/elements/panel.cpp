#include <ui/elements/panel.hpp>

#include <engine/util/text.hpp>

Panel::Panel(const sf::Font& font)
{
    text.setFont(font);
    text.setFillColor(Palette::white);

    frame.setFillColor(Palette::black);
    frame.setOutlineColor(Palette::white);
    frame.setOutlineThickness(outline);
}

void Panel::setPosition(const sf::Vector2f& position)
{
    frame.setPosition(position);
    text.setPosition(position + sf::Vector2f(padding, padding));
}

void Panel::setSize(const sf::Vector2f& size)
{
    frame.setSize(size);
    wrapText(text, frame.getSize().x - (padding * 2.f));
}

void Panel::setString(const std::string& string)
{
    text.setString(string);
    wrapText(text, frame.getSize().x - (padding * 2.f));
}

sf::Text& Panel::getText()
{
    return text;
}

void Panel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(frame, states);
    target.draw(text, states);
}
