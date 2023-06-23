#include <ui/hud/ai_turn.hpp>

AI_Turn::AI_Turn()
{
    elements.push_back(&system_info);
    panel_text.setFont(*font);
    panel_text.setFillColor(Palette::white);
    panel_text.setString("AI deciding...");

    std::string text = "AI_DECIDING";
    std::string loc = localize(text);
    panel_text.setString(loc);
    localize.recordPersistent(text, &panel_text);
}

void AI_Turn::enterState()
{
    clock.restart();
}

void AI_Turn::update(const sf::Vector2i& mpos)
{
    UI::update(mpos);
    if (clock.getElapsedTime().asSeconds() >= threshold) {
        setHUDState(UI::SIMULATE);
    }
}

void AI_Turn::windowResize(const sf::Vector2u& w_size)
{
    HUD::windowResize(w_size);
    sf::Vector2f panel_pos = turn_panel.getPosition() + sf::Vector2f(16.f, 16.f);
    panel_text.setPosition(panel_pos);
}

void AI_Turn::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.setView(view);
    target.draw(turn_panel, states);
    target.draw(panel_text, states);

    for (const auto& element : elements) {
        target.setView(view);
        target.draw(*element, states);
    }
}
