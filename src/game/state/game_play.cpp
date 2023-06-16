#include <game/state/game_play.hpp>

Game_Play::Game_Play()
{
}

Game_Play::~Game_Play()
{
    reset();
}

void Game_Play::update(const float delta_time)
{
    core->systems.update(delta_time);
}

void Game_Play::clickLeft()
{
    switch (core->systems.context()) {
        case Context::GALACTIC:
            core->systems.tile_system.activate();
            break;
        case Context::SOLAR:
            core->systems.solar_system.activate();
            break;
    }
}

void Game_Play::releaseLeft()
{ }

void Game_Play::clickRight()
{
    switch (core->systems.context()) {
        case Context::GALACTIC:
            core->systems.tile_system.deactivate();
            break;
        case Context::SOLAR:
            core->systems.solar_system.deactivate();
            break;
    }
}

void Game_Play::releaseRight()
{ }

void Game_Play::clickMiddle()
{
    const sf::Vector2f mpos = core->systems.relativeMousePos(*core->systems.context.current_view);
    core->systems.camera_controller.startDrag(mpos);
}

void Game_Play::releaseMiddle()
{
    const sf::Vector2f mpos = core->systems.relativeMousePos(*core->systems.context.current_view);
    core->systems.camera_controller.endDrag(mpos);
}
