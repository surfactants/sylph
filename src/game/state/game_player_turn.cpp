#include <game/state/game_player_turn.hpp>

void Game_Player_Turn::update(const float delta_time)
{
    const sf::Vector2f mpos = relativeMousePos(*(systems->context.current_view));
    controlCamera(mpos, delta_time);
    contextUpdate(mpos);
}
