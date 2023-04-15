#include <game/state/game_play.hpp>

Game_Play::Game_Play()
{}

Game_Play::Game_Play(const Game& g)
{
    world = g.getWorld();
    entities = g.getEntities();
}

void Game_Play::update(float delta_time)
{}
