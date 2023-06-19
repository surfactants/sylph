#include <ui/elements/info_panel.hpp>

Info_Panel::Info_Panel()
{
}

void Info_Panel::loadFont(sf::Font* font)
{
    this->font = font;
    for (auto& t : text) {
        t.setFont(*font);
    }
}

bool Info_Panel::update(const sf::Vector2i& mpos)
{
    bool cnt = contains(mpos);
    return cnt;
}

void Info_Panel::clickLeft()
{
}

void Info_Panel::releaseLeft()
{
}

void Info_Panel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(frame, states);
    for (const auto& s : sprites) {
        target.draw(s, states);
    }
    for (const auto& t : text) {
        target.draw(t, states);
    }
    /*
    for (const auto& b : buttons) {
        target.draw(b, states);
    }
    */
}
