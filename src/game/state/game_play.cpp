#include <game/state/game_play.hpp>

Game_Play::Game_Play(const Game& g)
    : Game(g)
{
    //renderer.add(world.get());
}

Game_Play::~Game_Play()
{
    reset();
}

void Game_Play::update(float delta_time, const sf::Vector2f& mpos)
{ }

void Game_Play::clickLeft()
{ }

void Game_Play::releaseLeft()
{ }

void Game_Play::clickRight()
{ }

void Game_Play::releaseRight()
{ }
