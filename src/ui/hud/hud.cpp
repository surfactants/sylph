#include <ui/hud/hud.hpp>

#include <engine/resources/font_manager.hpp>


sf::Font* HUD::font { Font_Manager::get(Font::UI) };

std::function<void(UI::State)> HUD::setHUDState;

HUD::HUD()
{}

void HUD::update(const sf::Vector2i& mpos)
{
    UI::update(mpos);
}

void HUD::enterState()
{}

void HUD::exitState()
{}

void HUD::windowResize(const sf::Vector2u& w_size)
{
    setView(w_size);

    const float padding = Element::padding;
    sf::Vector2f si_pos;
    sf::Vector2f si_size;
    si_size.x = 320.f;
    si_size.y = w_size.y - (padding * 2.f) - si_size.x;
    si_pos.x = w_size.x - si_size.x - padding;
    si_pos.y = padding;
}
