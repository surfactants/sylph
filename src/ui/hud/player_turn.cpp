#include <ui/hud/player_turn.hpp>

Player_Turn::Player_Turn()
    : next_turn { Button("NEXT_TURN", *font, std::bind(nextTurn, this), 60) }
{
    next_turn.setPosition(sf::Vector2f(1600.f, 900.f));
    elements.push_back(&next_turn);
}

void Player_Turn::nextTurn()
{
    setHUDState(HUD::AI_TURN);
}
