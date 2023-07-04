#include <ui/elements/system_info.hpp>

System_Info::System_Info()
{
    frame.setFillColor(Palette::black);
    frame.setOutlineColor(Palette::white);
    frame.setOutlineThickness(2.f);
}

void System_Info::clear()
{
    sprites.clear();
    text.clear();
    //buttons.clear();
    entity = NULL_ENTITY;
}

void System_Info::addText(std::string str, unsigned int csize)
{
    text.push_back(sf::Text(str, *font, csize));
    text.back().setFillColor(Palette::white);
}

void System_Info::setText(sf::Vector2f offset)
{
    sf::Vector2f pos = frame.getPosition() + offset;
    for (auto& t : text) {
        t.setPosition(pos);
        wrapText(t, frame.getSize().x - (offset.x * 2.f));
        pos.y += t.getLocalBounds().top + t.getLocalBounds().height + offset.y;
    }
}

void System_Info::setSize(sf::Vector2f size)
{
    frame.setSize(size);
}
