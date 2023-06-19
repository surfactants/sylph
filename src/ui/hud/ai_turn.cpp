#include <ui/hud/ai_turn.hpp>

AI_Turn::AI_Turn()
{
    elements.push_back(&system_info);
}

void AI_Turn::enterState()
{
    clock.restart();
}

void AI_Turn::update(const sf::Vector2i& mpos)
{
    UI::update(mpos);
    if (clock.getElapsedTime().asSeconds() >= threshold) {
        setHUDState(UI::PLAYER_TURN);
    }
}
