#include <ui/hud/ai_turn.hpp>

AI_Turn::AI_Turn()
{
    std::string text = "AI_DECIDING";
    std::string loc = localize(text);
    panel_text.setString(loc);
    localize.recordPersistent(text, &panel_text);

    panel_text.setFillColor(Palette::white);
    panel_text.setFont(*font);
}

void AI_Turn::enterState()
{
    clock.restart();

    turn_panel->addText(&panel_text, Panel::CENTER, turn_panel->getSize().x);
}

void AI_Turn::exitState()
{
    turn_panel->clear();
}

void AI_Turn::update(const sf::Vector2i& mpos)
{
    UI::update(mpos);
    if (clock.getElapsedTime().asSeconds() >= threshold) {
        setHUDState(UI::SIMULATE);
    }
}
