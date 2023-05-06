#include <game/state/game_play.hpp>

Game_Play::Game_Play()
{
}

Game_Play::~Game_Play()
{
    reset();
}

void Game_Play::update(float delta_time)
{
    systems.update(delta_time);
}

void Game_Play::clickLeft()
{
    switch (systems.context()) {
        case Context::GALACTIC:
            systems.tile_system.activate();
            break;
        case Context::SOLAR:
            break;
    }
}

void Game_Play::releaseLeft()
{ }

void Game_Play::clickRight()
{
    systems.tile_system.deactivate();
}

void Game_Play::releaseRight()
{ }
