#include <ui/hud/ai_turn.hpp>

AI_Turn::AI_Turn()
{}

void AI_Turn::enterState()
{
    clock.restart();

    std::string text = "AI_DECIDING";
    std::string loc = localize(text);
    turn_panel->setString(loc);
    localize.record(text, &turn_panel->getText());
}

void AI_Turn::exitState()
{
    localize.erase(&turn_panel->getText());
}

void AI_Turn::update(const sf::Vector2i& mpos)
{
    UI::update(mpos);
    if (clock.getElapsedTime().asSeconds() >= threshold) {
        setHUDState(UI::SIMULATE);
    }
}
