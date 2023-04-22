#include <game/state/game_play.hpp>

Game_Play::Game_Play()
{
}

Game_Play::Game_Play(const Game& g)
    : Game(g)
{
}

Game_Play::~Game_Play()
{
    world.reset();
}

void Game_Play::update(float delta_time)
{
}
