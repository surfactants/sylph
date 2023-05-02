#include <game/state/game_play.hpp>

Game_Play::Game_Play()
{
    renderer.add(&systems.tile_renderer);

    systems.accelerator.setMaxSpeed(10.f);
    systems.accelerator.setAcceleration(1.f);
}

Game_Play::~Game_Play()
{
    reset();
}

void Game_Play::update(float delta_time, const sf::Vector2f& mpos)
{
    systems.update(delta_time, mpos);
}

void Game_Play::clickLeft()
{ }

void Game_Play::releaseLeft()
{ }

void Game_Play::clickRight()
{ }

void Game_Play::releaseRight()
{ }
