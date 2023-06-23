#include <ui/hud/hud_simulate.hpp>

HUD_Simulate::HUD_Simulate()
{
    elements.push_back(&system_info);
    panel_text.setFont(*font);
    panel_text.setFillColor(Palette::white);

    std::string text = "SIMULATING";
    std::string loc = localize(text);
    panel_text.setString(loc);
    localize.recordPersistent(text, &panel_text);
}

void HUD_Simulate::enterState()
{
    clock.restart();
}

void HUD_Simulate::update(const sf::Vector2i& mpos)
{
    UI::update(mpos);
    if (clock.getElapsedTime().asSeconds() >= threshold) {
        setHUDState(UI::PLAYER_TURN);
    }
}

void HUD_Simulate::windowResize(const sf::Vector2u& w_size)
{
    HUD::windowResize(w_size);
    sf::Vector2f panel_pos = turn_panel.getPosition() + sf::Vector2f(16.f, 16.f);
    panel_text.setPosition(panel_pos);
}

void HUD_Simulate::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.setView(view);
    target.draw(turn_panel, states);
    target.draw(panel_text, states);

    for (const auto& element : elements) {
        target.setView(view);
        target.draw(*element, states);
    }
}
